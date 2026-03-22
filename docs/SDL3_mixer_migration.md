# SDL3_mixer 迁移说明 (SDL2_mixer API → SDL3_mixer 3.2.0)

## 背景

SDL3_mixer 3.2.0 正式版对 API 进行了彻底重构，废弃了旧的 **Channel/Music 二元模型**，改为统一的 **Track-based 架构**。本项目采用最小迁移方案完成适配。

> 官方迁移指南：https://wiki.libsdl.org/SDL3_mixer/README-migration

## 架构变化概览

### 旧架构 vs 新架构

```mermaid
flowchart LR
  subgraph OLD["旧架构 (SDL2_mixer 风格)"]
    direction TB
    Music["Mix_Music<br/>独立音乐通道（全局唯一）"]
    Channels["Mix_Chunk<br/>Channel 0 | Channel 1 | ... | Channel 15"]
    Music ~~~ Channels
  end

  subgraph NEW["新架构 (SDL3_mixer 3.2.0)"]
    direction TB
    Mixer["MIX_Mixer (混音器实例)"]
    Track1["MIX_Track ← MIX_Audio"]
    Track2["MIX_Track ← MIX_Audio"]
    TrackN["... 按需创建更多轨道"]
    FAF["fire-and-forget 内部轨道池"]
    Mixer ~~~ Track1 ~~~ Track2 ~~~ TrackN ~~~ FAF
  end

  OLD ~~~ NEW

  style OLD fill:#fee,stroke:#c33
  style NEW fill:#efe,stroke:#3a3
```

**核心变化：**
- `Mix_Chunk` + `Mix_Music` → 统一为 `MIX_Audio`（不再区分音效和音乐）
- 索引式 Channel 分配 → 指针式 `MIX_Track` 管理
- 全局单例混音器 → 显式 `MIX_Mixer` 对象

### 类型映射关系

```mermaid
graph LR
  subgraph 旧类型
    A1[Mix_Chunk *]
    A2[Mix_Music *]
    A3["(无)"]
    A4["(无)"]
  end

  subgraph 新类型
    B1[MIX_Audio *]
    B2[MIX_Mixer *]
    B3[MIX_Track *]
  end

  A1 -- 统一 --> B1
  A2 -- 统一 --> B1
  A3 -- 新增 --> B2
  A4 -- 新增 --> B3

  style A1 fill:#fdd,stroke:#c33
  style A2 fill:#fdd,stroke:#c33
  style B1 fill:#dfd,stroke:#3a3
  style B2 fill:#dfd,stroke:#3a3
  style B3 fill:#dfd,stroke:#3a3
```

## 涉及文件

```mermaid
graph TB
  subgraph 变更文件
    AH["asset_store.h<br/>类型替换 + 构造函数签名"]
    AC["asset_store.cpp<br/>加载/释放函数替换"]
    GH["game.h<br/>新增 mixer/track 成员<br/>音频方法声明重写"]
    GC["game.cpp<br/>初始化/清理/播放逻辑重写"]
  end

  AH --> AC
  GH --> GC
  GC -- 调用 --> AC

  style AH fill:#ffd,stroke:#aa0
  style AC fill:#ffd,stroke:#aa0
  style GH fill:#ffd,stroke:#aa0
  style GC fill:#ffd,stroke:#aa0
```

## 详细变更

### 1. 初始化流程 (`game.cpp` → `Game::init`)

```mermaid
graph TD
  subgraph 旧流程
    direction TB
    O1["Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG)"] --> O2["Mix_OpenAudio(0, NULL)"]
    O2 --> O3["Mix_AllocateChannels(16)"]
    O3 --> O4["Mix_VolumeMusic(MIX_MAX_VOLUME / 4)"]
    O4 --> O5["Mix_Volume(-1, MIX_MAX_VOLUME / 4)"]
  end

  subgraph 新流程
    direction TB
    N1["MIX_Init()"] --> N2["MIX_CreateMixerDevice(<br/>SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL)"]
    N2 --> N3["MIX_CreateTrack(mixer_)"]
    N3 --> N4["MIX_SetMixerGain(mixer_, 0.25f)"]
  end

  style O1 fill:#fdd,stroke:#c33
  style O2 fill:#fdd,stroke:#c33
  style O3 fill:#fdd,stroke:#c33
  style O4 fill:#fdd,stroke:#c33
  style O5 fill:#fdd,stroke:#c33
  style N1 fill:#dfd,stroke:#3a3
  style N2 fill:#dfd,stroke:#3a3
  style N3 fill:#dfd,stroke:#3a3
  style N4 fill:#dfd,stroke:#3a3
```

**要点：**
- `MIX_Init()` 无参数，内部自动检测可用解码器
- 不再需要 `Mix_AllocateChannels`，轨道按需创建
- 音量从 `int (0-128)` 改为 `float (0.0-1.0+)`，`MIX_MAX_VOLUME` 已移除

### 2. 音频加载 (`asset_store.cpp`)

```mermaid
graph LR
  subgraph 旧 API
    L1["Mix_LoadWAV(path)"]
    L2["Mix_LoadMUS(path)"]
    F1["Mix_FreeChunk(chunk)"]
    F2["Mix_FreeMusic(music)"]
  end

  subgraph 新 API
    L3["MIX_LoadAudio(mixer, path, true)<br/>预解码，适合音效"]
    L4["MIX_LoadAudio(mixer, path, false)<br/>流式解码，适合音乐"]
    F3["MIX_DestroyAudio(audio)"]
  end

  L1 --> L3
  L2 --> L4
  F1 --> F3
  F2 --> F3

  style L1 fill:#fdd,stroke:#c33
  style L2 fill:#fdd,stroke:#c33
  style F1 fill:#fdd,stroke:#c33
  style F2 fill:#fdd,stroke:#c33
  style L3 fill:#dfd,stroke:#3a3
  style L4 fill:#dfd,stroke:#3a3
  style F3 fill:#dfd,stroke:#3a3
```

`AssetStore` 构造函数新增 `MIX_Mixer*` 参数，因为 `MIX_LoadAudio` 需要 mixer 上下文。

### 3. 音乐播放 (`game.cpp` → `Game::playMusic`)

```mermaid
sequenceDiagram
    participant 调用者
    participant Game
    participant MIX as SDL3_mixer

    Note over Game,MIX: 旧流程（单行调用）
    调用者->>Game: playMusic(path, loop)
    Game->>MIX: Mix_PlayMusic(music, loop ? -1 : 0)

    Note over Game,MIX: 新流程（轨道式）
    调用者->>Game: playMusic(path, loop)
    Game->>MIX: MIX_StopTrack(music_track_, 0)
    Game->>MIX: MIX_SetTrackAudio(music_track_, audio)
    alt loop = true
        Game->>MIX: SDL_CreateProperties()
        Game->>MIX: SDL_SetNumberProperty(props, LOOPS, -1)
        Game->>MIX: MIX_PlayTrack(music_track_, props)
        Game->>MIX: SDL_DestroyProperties(props)
    else loop = false
        Game->>MIX: MIX_PlayTrack(music_track_, 0)
    end
```

**要点：**
- 播放前需手动设置轨道的音频输入 (`MIX_SetTrackAudio`)
- 循环等参数通过 `SDL_Properties` 传递（`-1` = 无限循环）
- `MIX_PlayTrack` 第二个参数传 `0` 表示使用默认选项

### 4. 音效播放 (`game.h` → `Game::playSound`)

```mermaid
sequenceDiagram
    participant 调用者
    participant Game
    participant MIX as SDL3_mixer

    Note over Game,MIX: 旧流程（通道式）
    调用者->>Game: playSound(path)
    Game->>MIX: Mix_PlayChannel(-1, chunk, 0)
    Note right of MIX: 自动选择空闲 Channel

    Note over Game,MIX: 新流程（fire-and-forget）
    调用者->>Game: playSound(path)
    Game->>MIX: MIX_PlayAudio(mixer_, audio)
    Note right of MIX: 内部自动创建临时轨道<br/>播完自动回收
```

采用 **fire-and-forget** 模式：SDL_mixer 内部自动管理临时轨道，播放完毕自动回收。适合一次性音效（UI 点击、打击音等）。

### 5. 播放控制 (`game.h`)

```mermaid
graph LR
  subgraph 旧 API
    H1["Mix_HaltMusic()"]
    H2["Mix_HaltChannel(-1)"]
    P1["Mix_PauseMusic()"]
    P2["Mix_Pause(-1)"]
    R1["Mix_ResumeMusic()"]
    R2["Mix_Resume(-1)"]
  end

  subgraph 新 API
    S1["MIX_StopTrack(music_track_, 0)"]
    S2["MIX_StopAllTracks(mixer_, 0)"]
    PA1["MIX_PauseTrack(music_track_)"]
    PA2["MIX_PauseAllTracks(mixer_)"]
    RE1["MIX_ResumeTrack(music_track_)"]
    RE2["MIX_ResumeAllTracks(mixer_)"]
  end

  H1 --> S1
  H2 --> S2
  P1 --> PA1
  P2 --> PA2
  R1 --> RE1
  R2 --> RE2

  style H1 fill:#fdd,stroke:#c33
  style H2 fill:#fdd,stroke:#c33
  style P1 fill:#fdd,stroke:#c33
  style P2 fill:#fdd,stroke:#c33
  style R1 fill:#fdd,stroke:#c33
  style R2 fill:#fdd,stroke:#c33
  style S1 fill:#dfd,stroke:#3a3
  style S2 fill:#dfd,stroke:#3a3
  style PA1 fill:#dfd,stroke:#3a3
  style PA2 fill:#dfd,stroke:#3a3
  style RE1 fill:#dfd,stroke:#3a3
  style RE2 fill:#dfd,stroke:#3a3
```

### 6. 清理流程 (`game.cpp` → `Game::clean`)

```mermaid
graph TD
  subgraph 旧流程
    direction TB
    C1["Mix_CloseAudio()"] --> C2["Mix_Quit()"]
  end

  subgraph 新流程
    direction TB
    D1["MIX_DestroyTrack(music_track_)"] --> D2["MIX_DestroyMixer(mixer_)"]
    D2 --> D3["MIX_Quit()"]
  end

  style C1 fill:#fdd,stroke:#c33
  style C2 fill:#fdd,stroke:#c33
  style D1 fill:#dfd,stroke:#3a3
  style D2 fill:#dfd,stroke:#3a3
  style D3 fill:#dfd,stroke:#3a3
```

## 本项目完整音频生命周期

```mermaid
graph TD
  Init["Game::init()"] --> MixInit["MIX_Init()"]
  MixInit --> CreateMixer["mixer_ = MIX_CreateMixerDevice(...)"]
  CreateMixer --> CreateTrack["music_track_ = MIX_CreateTrack(mixer_)"]
  CreateTrack --> SetGain["MIX_SetMixerGain(mixer_, 0.25f)"]
  SetGain --> CreateStore["asset_store_ = new AssetStore(renderer_, mixer_)"]
  CreateStore --> Ready["就绪"]

  Ready --> PlayMusic["playMusic(path, loop)"]
  Ready --> PlaySound["playSound(path)"]

  PlayMusic --> LoadM["MIX_LoadAudio(mixer_, path, false)"]
  LoadM --> SetAudio["MIX_SetTrackAudio(music_track_, audio)"]
  SetAudio --> PlayTrack["MIX_PlayTrack(music_track_, props)"]

  PlaySound --> LoadS["MIX_LoadAudio(mixer_, path, true)"]
  LoadS --> FireForget["MIX_PlayAudio(mixer_, audio)"]

  Ready --> Cleanup["Game::clean()"]
  Cleanup --> CleanStore["asset_store_->clean()<br/>MIX_DestroyAudio() x N"]
  CleanStore --> DestroyTrack["MIX_DestroyTrack(music_track_)"]
  DestroyTrack --> DestroyMixer["MIX_DestroyMixer(mixer_)"]
  DestroyMixer --> Quit["MIX_Quit()"]

  style Init fill:#adf,stroke:#36a
  style Ready fill:#ffa,stroke:#aa0
  style Cleanup fill:#faa,stroke:#a33
  style PlayMusic fill:#afa,stroke:#3a3
  style PlaySound fill:#afa,stroke:#3a3
```

## 迁移策略

采用 **最小迁移方案**，保持代码逻辑和规模与迁移前一致：

```mermaid
mindmap
  root((迁移策略))
    音乐
      专用 MIX_Track
      支持循环/暂停/恢复/停止
      流式解码 predecode=false
    音效
      MIX_PlayAudio fire-and-forget
      无需手动管理轨道
      预解码 predecode=true
    音量
      MIX_SetMixerGain 统一主音量
      浮点数 0.0 ~ 1.0+
      替代分别设置音乐/音效音量
    未引入的高级特性
      标签分组 TagTrack
      3D 空间音频
      回调钩子
      音频解码器 API
```
