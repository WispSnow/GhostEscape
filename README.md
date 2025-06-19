# GhostEscape
利用SDL3、GLM开发一款生存类型的游戏

([C++游戏开发之旅](https://pan.baidu.com/s/1xGGgZbhE6WuSPzlKuTmdMw?pwd=wd9g) 第二期)

## 项目简介
此项目为教学演示用途，配套教程：[视频](https://www.bilibili.com/video/BV1jf9XYQEhW/)，[文字](https://cppgamedev.top/courses/modular-ghost-escape)

>因网络时常不稳定，环境安装包及代码均可从[百度网盘](https://pan.baidu.com/s/16OuMaAqehGjzSoMS19zNcA?pwd=5brp)中下载。如果使用`Library.zip`，则只需要配置环境变量即可（代码版本可能落后于Github仓库）

提示：仓库中包含了所有课节的代码，你可以根据视频教程的进度查找对应的代码。<img src="https://theorhythm.top/gamedev/tags.png" style='width: 400px;' />
<img src="https://theorhythm.top/gamedev/download.png" style='width: 800px;' />

或者使用Git更加方便地查看代码，参考此教程：[利用Git快速查看课节代码](https://www.bilibili.com/video/BV1H7KGerEAa/)

本项目为CC0 1.0许可，这意味着你可以随意使用此代码且无需署名，但如果你给出Github链接或者视频教程的链接，我会非常感激。

## 游戏截图
<img src="https://theorhythm.top/gamedev/GE/screen_ge_1.png" style='width: 600px;'/>
<img src="https://theorhythm.top/gamedev/GE/screen_ge_2.png" style='width: 600px;'/>
<img src="https://theorhythm.top/gamedev/GE/screen_ge_3.png" style='width: 600px;'/>

## 环境配置
请根据你自己的平台（Linux、MacOS、Windows）参考各自的配置方法。
<img src="https://theorhythm.top/gamedev/GE/de0aeb654956613ce73dfbe60156be34.png" />
其中C++编译器、CMake、SDL、VS Code的安装方法及相关配置已经在上一期教程中说明，请参见 [Github仓库](https://github.com/WispSnow/SDLShooter) 或 视频演示（[环境安装](https://www.bilibili.com/video/BV1KkCFY4EKH/)、[VScode配置](https://www.bilibili.com/video/BV17bCBYSEAY)、[CMake配置](https://www.bilibili.com/video/BV19CCHYNEvQ)）。**但是要特别注意，SDL的版本需要是“SDL3”而非“SDL2”。** SDL2版本只适用于上一期教程。
> 查看最新版本的SDL库：[SDL](https://github.com/libsdl-org/SDL/releases/)，[SDL_image](https://github.com/libsdl-org/SDL_image/releases)，[SDL_mixer](https://github.com/libsdl-org/SDL_mixer/releases)，[SDL_ttf](https://github.com/libsdl-org/SDL_ttf/releases) 

提示：目前SDL_mixer并未发布3.x版本，自己编译比较繁琐（方法参见[视频教程](https://www.bilibili.com/video/BV1J2RpYGEmj/)），建议直接使用我在[百度网盘](https://pan.baidu.com/s/16OuMaAqehGjzSoMS19zNcA?pwd=5brp)中整理好的第三方库文件

此处补充 GLM 安装方法（请确保其它组件成功安装后再安装GLM）：
### Ubuntu Linux
1. 打开终端，输入：
```bash
sudo apt install libglm-dev
```
显示成功即完成配置。

### MacOS
1. 确保你的电脑安装了homebrew，之后打开终端输入：
	```bash
	brew install glm
	```
显示成功即完成配置。

### Windows
1. 打开[GLM官方仓库](https://github.com/g-truc/glm)并下载源代码<img src="https://theorhythm.top/gamedev/GE/d028a691f02936d67ca2213fad65b347.png" style='width: 800px;' /> 解压后用VS Code打开源码文件夹，并按照提示执行CMake配置。配置完毕后执行“生成”<img src="https://theorhythm.top/gamedev/GE/fb8c05b89d0f7d56a36da101d346ee9f.png" style='width: 800px;' /> 等待生成结束后，打开左侧资源管理器中的build文件夹，点开“cmake_install.cmake”文件，修改其中的 `CMAKE_INSTALL_PREFIX` 参数为你想要安装的位置。我这里设为C盘的Library文件夹。保存文件后打开“命令”面板（ctrl+shift+p），执行“Cmake 安装” <img src="https://theorhythm.top/gamedev/GE/23eafac4b5dd65dc74b8f6f813c53cf2.png" style='width: 800px;' /><img src="https://theorhythm.top/gamedev/GE/4a47de83c5bc810406ea8f0083ff3880.png" style='width: 800px;' /> 成功后即可在目标地址看到glm文件夹<img src="https://theorhythm.top/gamedev/GE/6d4bc25ee118046ca687c9fadd750207.png" style='width: 800px;' />
> 如果因为网络因素下载困难，也可以直接使用我下载/编译的库：[百度网盘](https://pan.baidu.com/s/16OuMaAqehGjzSoMS19zNcA?pwd=5brp)，版本与教程相同

2. 设置环境变量，将上一步得到的`文件夹路径` 及 `文件夹路径\lib` 添加到Path变量中<img src="https://theorhythm.top/gamedev/GE/28cb49a9b87c96a009e0d7fb15a2b566.png" />
至此完成配置。

## CMakeLists.txt 补充
要添加GLM的支持，只需要在上期课程的代码中添加 `find_package(glm CONFIG REQUIRED)` 和 `glm::glm` 两行即可。<img src="https://theorhythm.top/gamedev/GE/7b847d543c9161b9191d6eafd7dfce53.png" style='width: 800px;' />

## 素材包下载
[百度网盘](https://pan.baidu.com/s/1kgTPgg40C1DRDA-B6UOzbA?pwd=5v8t)

## 致谢
游戏素材来自于以下作者，感谢他们的贡献：
- 精灵图
    - https://caz-creates-games.itch.io/ghost
    - https://master-blazter.itch.io/ghostspritepack
- 特效
    - https://bdragon1727.itch.io/750-effect-and-fx-pixel-all
    - https://pimen.itch.io/fire-spell
    - https://pimen.itch.io/thunder-spell-effect-02
- 文字
    - https://www.fontspace.com/super-shiny-font-f126184
- UI
    - https://kaboff.itch.io/160-cursors-crosshairs-pack-32x32
    - https://bdragon1727.itch.io/platformer-ui-buttons
    - https://adwitr.itch.io/pixel-health-bar-asset-pack-2
    - https://jaqmarti.itch.io/modern-mobile-ui
    - https://markiro.itch.io/hud-asset-pack
    - https://candycorrin.itch.io/fantasy-element-ui-icons
    - https://kenney-assets.itch.io/cursor-pack
- 音效
    - https://kasse.itch.io/ui-buttons-sound-effects-pack
    - https://pixabay.com/sound-effects/big-thunder-clap-99753/
    - https://pixabay.com/sound-effects/080167-female-scream-02-89290/
- 音乐
    - https://games-for-all-7.itch.io/spooky-music
    - https://poltergasm.itch.io/oh-my-ghost-music

