# 标题
cmake_minimum_required(VERSION 3.10.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置编译选项
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 设置编译输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(glm REQUIRED)

# 设置通用源文件
set(SOURCES
    src/core/game.cpp
    src/core/asset_store.cpp
    src/core/object.cpp
    src/core/object_world.cpp
    src/core/object_affiliate.cpp
    src/core/scene.cpp
    src/core/actor.cpp
    src/screen/ui_mouse.cpp
    src/screen/hud_stats.cpp
    src/screen/hud_skill.cpp
    src/screen/hud_text.cpp
    src/screen/hud_button.cpp
    src/raw/stats.cpp
    src/raw/weapon.cpp
    src/raw/timer.cpp
    src/raw/bg_star.cpp
    src/world/effect.cpp
    src/world/spell.cpp
    src/affiliate/sprite.cpp
    src/affiliate/sprite_anim.cpp
    src/affiliate/collider.cpp
    src/affiliate/affiliate_bar.cpp
    src/affiliate/text_label.cpp
    src/spawner.cpp
    src/player.cpp
    src/enemy.cpp
    src/weapon_thunder.cpp
    src/main.cpp
    src/scene_title.cpp
    src/scene_main.cpp
)

# 根据平台向"通用源文件"追加平台专属的文件
if(WIN32)
    # 如果是 Windows 平台, 将资源文件追加到源文件列表
    list(APPEND SOURCES resources.rc)
endif()
# TODO: MacOS 和 Linux 平台

# 添加可执行文件, 使用配置好的 "SOURCES" 变量
add_executable(${TARGET} ${SOURCES})

# 链接库
target_link_libraries(${TARGET}
                        ${SDL3_LIBRARIES}
                        SDL3_image::SDL3_image
                        SDL3_mixer::SDL3_mixer
                        SDL3_ttf::SDL3_ttf
                        glm::glm
                        )

# 不要弹出控制台窗口
if (MSVC)
    target_link_options(${TARGET} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()