# ============================================
# 项目主配置文件
# ============================================
cmake_minimum_required(VERSION 3.10.0)
project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

# ============================================
# 基础配置
# ============================================

# 指定搜索路径（用于find_package在编译期查找库）
set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/prebuilt)

# 指定目标名称
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# 依赖库默认链接类型：ON = 动态链接(.dll/.so/.dylib)，OFF = 静态链接(.lib/.a)
# 注意：可以在Dependencies.cmake中为每个库单独指定
option(BUILD_SHARED_LIBS "依赖库默认编译为动态库" OFF)

# ============================================
# 引入模块化配置
# ============================================

# 编译器设置（C++标准、编译选项等）
include(cmake/CompilerSettings.cmake)

# 运行时路径配置（RPATH）
include(cmake/RuntimePath.cmake)

# 依赖管理
include(cmake/Dependencies.cmake)

# 构建辅助函数
include(cmake/BuildHelpers.cmake)

# 项目信息打印
include(cmake/ProjectInfo.cmake)

# ============================================
# 设置项目依赖
# ============================================

# 调用依赖配置函数（定义在Dependencies.cmake中）
setup_project_dependencies()

# ============================================
# 项目源文件
# ============================================

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

# Windows平台添加资源文件
if(WIN32)
    list(APPEND SOURCES resources.rc)
endif()

# ============================================
# 可执行文件配置
# ============================================

# 创建可执行文件
add_executable(${TARGET} ${SOURCES})

# 链接所有依赖库
target_link_libraries(${TARGET}
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)

# ============================================
# 应用配置
# ============================================

# 设置编译选项（定义在CompilerSettings.cmake中）
setup_compiler_options(${TARGET})

# 配置资源文件复制（定义在BuildHelpers.cmake中）
setup_asset_copy(${TARGET})

# 配置Windows DLL复制（定义在BuildHelpers.cmake中）
setup_windows_dll_copy(${TARGET})

# ============================================
# 打印配置信息
# ============================================

# 打印项目配置完成信息（定义在ProjectInfo.cmake中）
print_project_info(${TARGET})
