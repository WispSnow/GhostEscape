[English](README.md) | **简体中文**

# GhostEscape
**GhostEscape** 是一款使用 C++、SDL3 和 glm 开发的跨平台生存游戏。

> 本项目是一个教学演示项目；它是系列教程“[C++ 游戏开发之旅](https://cppgamedev.top/)”的第 2 集。

## 控制
```
W,A,S,D - 移动;
鼠标左键 - 攻击;
鼠标右键 - 慢动作;
F4 - 切换全屏;
```

## 网页版试玩
[GhostEscape](https://wispsnow.github.io/GhostEscape/)

## 截图
<img src="https://theorhythm.top/gamedev/GE/screen_ge_1.png" style='width: 600px;'/>
<img src="https://theorhythm.top/gamedev/GE/screen_ge_2.png" style='width: 600px;'/>
<img src="https://theorhythm.top/gamedev/GE/screen_ge_3.png" style='width: 600px;'/>

## 第三方库
* [SDL3](https://github.com/libsdl-org/SDL)
* [SDL3_image](https://github.com/libsdl-org/SDL_image)
* [SDL3_mixer](https://github.com/libsdl-org/SDL_mixer)
* [SDL3_ttf](https://github.com/libsdl-org/SDL_ttf)
* [glm](https://github.com/g-truc/glm)

## 如何构建
依赖项将通过 Git FetchContent 自动下载，构建非常简单：
```bash
git clone https://github.com/WispSnow/GhostEscape.git
cd GhostEscape
cmake -S . -B build
cmake --build build
```

如果您在从 GitHub 下载时遇到问题（尤其是在中国大陆网络环境下），请参考 [wiki](../../wiki) 获取替代构建指南。

## 鸣谢 (Credits)
- sprite
    - https://caz-creates-games.itch.io/ghost
    - https://master-blazter.itch.io/ghostspritepack
- FX
    - https://bdragon1727.itch.io/750-effect-and-fx-pixel-all
    - https://pimen.itch.io/fire-spell
    - https://pimen.itch.io/thunder-spell-effect-02
- font
    - https://www.fontspace.com/super-shiny-font-f126184
- UI
    - https://kaboff.itch.io/160-cursors-crosshairs-pack-32x32
    - https://bdragon1727.itch.io/platformer-ui-buttons
    - https://adwitr.itch.io/pixel-health-bar-asset-pack-2
    - https://jaqmarti.itch.io/modern-mobile-ui
    - https://markiro.itch.io/hud-asset-pack
    - https://candycorrin.itch.io/fantasy-element-ui-icons
    - https://kenney-assets.itch.io/cursor-pack
- sound
    - https://kasse.itch.io/ui-buttons-sound-effects-pack
    - https://pixabay.com/sound-effects/big-thunder-clap-99753/
    - https://pixabay.com/sound-effects/080167-female-scream-02-89290/
- music
    - https://games-for-all-7.itch.io/spooky-music
    - https://poltergasm.itch.io/oh-my-ghost-music

- 赞助者: `sino`, `李同学` 

## 联系方式

如需支持或反馈，请通过本仓库的 GitHub issues 版块联系我们。您的反馈对于改进本系列教程至关重要！

## 请我喝杯咖啡
<a href="https://ko-fi.com/ziyugamedev"><img src="https://storage.ko-fi.com/cdn/kofi2.png?v=3" alt="Buy Me A Coffee" width="200" /></a>
<a href="https://afdian.com/a/ziyugamedev"><img src="https://pic1.afdiancdn.com/static/img/welcome/button-sponsorme.png" alt="Support me on Afdian" width="200" /></a>


## QQ 交流群和我的微信二维码

<div style="display: flex; gap: 10px;">
  <img src="https://theorhythm.top/personal/qq_group.webp" width="200" />
  <img src="https://theorhythm.top/personal/wechat_qr.webp" width="200" />
</div>
