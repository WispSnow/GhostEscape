#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>
#include <random>
#include "asset_store.h"

struct Texture;
class Scene;
class Game
{
    AssetStore* asset_store_ = nullptr; // 资源管理器
    glm::vec2 screen_size_ = glm::vec2(0); // 屏幕大小
    
    glm::vec2 mouse_position_ = glm::vec2(0);
    SDL_MouseButtonFlags mouse_buttons_ = 0;
    bool is_running_ = true; // 游戏是否运行
    Scene* current_scene_ = nullptr; // 当前场景
    Scene* next_scene_ = nullptr;

    Uint64 FPS_ = 60; // 游戏帧率
    Uint64 frame_delay_ = 0; // 帧延迟，单位ns
    float dt_ = 0.0f; // 帧间隔

    int score_ = 0;
    int high_score_ = 0;

    SDL_Window* window_ = nullptr; // 窗口
    SDL_Renderer* renderer_ = nullptr; // 渲染器
    TTF_TextEngine* ttf_engine_ = nullptr;

    std::mt19937 gen_ = std::mt19937(std::random_device{}());

    // 私有构造函数
    Game(){}
    // 禁止拷贝构造函数与赋值操作符
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

public:
    static Game& getInstance()
    {
        static Game instance;
        return instance;
    }

    void run(); // 运行游戏, 执行游戏主循环
    void init(std::string title, int width, int height); // 初始化游戏
    void handleEvents(); // 处理事件
    void update(float dt); // 更新游戏状态
    void render(); // 渲染游戏
    void clean(); // 清理游戏资源

    // getters and setters
    glm::vec2 getScreenSize() const { return screen_size_; } // 获取屏幕大小
    Scene* getCurrentScene() const { return current_scene_; } // 获取当前场景
    AssetStore* getAssetStore() const { return asset_store_; } // 获取资源管理器
    glm::vec2 getMousePosition() const { return mouse_position_; } // 获取鼠标位置
    SDL_MouseButtonFlags getMouseButtons() const { return mouse_buttons_; } // 获取鼠标按钮
    void setScore(int score) ;
    int getScore() const { return score_; } // 获取分数
    void setHighScore(int high_score) { high_score_ = high_score; } // 设置最高分数
    int getHighScore() const { return high_score_; } // 获取最高分数

    void addScore(int score);
    void quit() { is_running_ = false; }
    void safeChangeScene(Scene* scene) { next_scene_ = scene; }
    void changeScene(Scene* scene);

    // 音频函数
    void playMusic(const std::string& music_path, bool loop = true) { Mix_PlayMusic(asset_store_->getMusic(music_path), loop ? -1 : 0); } //-1代表无限循环
    void playSound(const std::string& sound_path) { Mix_PlayChannel(-1, asset_store_->getSound(sound_path), 0); }
    void stopMusic() { Mix_HaltMusic(); }
    void stopSound() { Mix_HaltChannel(-1); }       // 停止所有音效
    void pauseMusic() { Mix_PauseMusic(); }
    void pauseSound() { Mix_Pause(-1); }
    void resumeMusic() { Mix_ResumeMusic(); }
    void resumeSound() { Mix_Resume(-1); }

    // 随机数函数
    float randomFloat(float min, float max) { return std::uniform_real_distribution<float>(min, max)(gen_); }
    int randomInt(int min, int max) { return std::uniform_int_distribution<int>(min, max)(gen_); }
    glm::vec2 randomVec2(const glm::vec2& min, const glm::vec2& max) { return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y)); }
    glm::ivec2 randomIVec2(const glm::ivec2& min, const glm::ivec2& max) { return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y)); }

    // 渲染函数
    void renderTexture(const Texture& texture, const glm::vec2& position, const glm::vec2& size, const glm::vec2 &mask = glm::vec2(1.0f)); // 渲染纹理
    void renderFillCircle(const glm::vec2& position, const glm::vec2& size, float alpha);
    void renderHBar(const glm::vec2& position, const glm::vec2& size, float percent, SDL_FColor color);
    void drawGrid(const glm::vec2& top_left, const glm::vec2& botton_right, float grid_width, SDL_FColor fcolor); // 绘制网格
    void drawBoundary(const glm::vec2& top_left, const glm::vec2& botton_right, float boundary_width, SDL_FColor fcolor); // 绘制边界
    void drawPoints(const std::vector<glm::vec2>& points, glm::vec2 render_pos, SDL_FColor fcolor);

    // 文字函数
    TTF_Text* createTTF_Text(const std::string& text, const std::string& font_path, int font_size = 16);

    // 工具函数
    bool isMouseInRect(const glm::vec2& top_left, const glm::vec2& botton_right);
    std::string loadTextFile(const std::string& file_path);

private:
    void updateMouse();
};

#endif // GAME_H