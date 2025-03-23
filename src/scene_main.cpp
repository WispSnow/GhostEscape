#include "scene_main.h"
#include "player.h"
#include "enemy.h"
#include "world/effect.h"
#include "spawner.h"
#include "screen/ui_mouse.h"
#include "world/spell.h"
#include "screen/hud_stats.h"
#include "screen/hud_text.h"
#include "screen/hud_button.h"
#include "scene_title.h"
#include "raw/timer.h"
#include "raw/bg_star.h"
#include <fstream>

void SceneMain::init()
{
    Scene::init();
    SDL_HideCursor();
    Game::getInstance()->playMusic("assets/bgm/OhMyGhost.ogg");
    world_size_ = Game::getInstance()->getScreenSize() * 3.0f;
    camera_position_ = world_size_ / 2.0f - Game::getInstance()->getScreenSize() / 2.0f;
    player_ = new Player();
    player_->init();
    player_->setPosition(world_size_ / 2.0f);
    addChild(player_);

    BgStar::addBgStarChild(this, 2000, 0.2, 0.5, 0.7);

    end_timer_ = Timer::addTimerChild(this);

    spawner_ = new Spawner();
    spawner_->init();
    spawner_->setTarget(player_);
    addChild(spawner_);

    button_pause_ = HUDButton::addHUDButtonChild(this, Game::getInstance()->getScreenSize() - glm::vec2(230.f, 30.f),"assets/UI/A_Pause1.png", "assets/UI/A_Pause2.png", "assets/UI/A_Pause3.png");
    button_restart_ = HUDButton::addHUDButtonChild(this, Game::getInstance()->getScreenSize() - glm::vec2(140.f, 30.f), "assets/UI/A_Restart1.png", "assets/UI/A_Restart2.png", "assets/UI/A_Restart3.png");
    button_back_ = HUDButton::addHUDButtonChild(this, Game::getInstance()->getScreenSize() - glm::vec2(50.f, 30.f), "assets/UI/A_Back1.png", "assets/UI/A_Back2.png", "assets/UI/A_Back3.png");

    hud_stats_ = HUDStats::addHUDStatsChild(this, player_, glm::vec2(30.f));
    hud_text_score_ = HUDText::addHUDTextChild(this, "Score: 0", glm::vec2(Game::getInstance()->getScreenSize().x - 120.f, 30.f), glm::vec2(200, 50));

    ui_mouse_ = UIMouse::addUIMouseChild(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, Anchor::CENTER);   // 最后添加
}

bool SceneMain::handleEvents(SDL_Event& event)
{
    if (Scene::handleEvents(event)) return true;
    return false;
}

void SceneMain::update(float dt)
{
    checkSlowDown(dt);
    Scene::update(dt);
    updateScore();
    checkButtonRestart();
    checkButtonPause();
    checkButtonBack();
    if (player_ && !player_->getActive()) 
    {
        end_timer_->start();
        saveData("assets/score.dat");
    }
    checkEndTimer();
}

void SceneMain::render()
{
    renderBackground();
    Scene::render();
}

void SceneMain::clean()
{
    Scene::clean();
}

void SceneMain::saveData(const std::string &file_path)
{
    auto score = Game::getInstance()->getHighScore();
    std::ofstream file(file_path, std::ios::binary);    // 以二进制形式保存
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&score), sizeof(score));
        file.close();
    }
}

void SceneMain::renderBackground()
{
    auto start = - camera_position_;
    auto end = world_size_ - camera_position_;
    Game::getInstance()->drawGrid(start, end, 80.0f, {0.5, 0.5, 0.5, 1.0});
    Game::getInstance()->drawBoundary(start, end, 5.0f, {1.0, 1.0, 1.0, 1.0});
}

void SceneMain::updateScore()
{
    hud_text_score_->setText("Score: " + std::to_string(Game::getInstance()->getScore()));
}

void SceneMain::checkButtonPause()
{
    if (!button_pause_->getIsTrigger()) return;
    if (is_pause_) resume();
    else pause();
}

void SceneMain::checkButtonRestart()
{
    if (!button_restart_->getIsTrigger()) return;
    saveData("assets/score.dat");
    Game::getInstance()->setScore(0);
    auto scene = new SceneMain();
    Game::getInstance()->safeChangeScene(scene); // 或者 当前场景 先clean() 再 init()
}

void SceneMain::checkButtonBack()
{
    if (!button_back_->getIsTrigger()) return;
    saveData("assets/score.dat");
    Game::getInstance()->setScore(0);
    auto scene = new SceneTitle();
    Game::getInstance()->safeChangeScene(scene);
}

void SceneMain::checkEndTimer()
{
    if (!end_timer_->timeOut()) return;
    pause();
    Game::getInstance()->resumeMusic();
    button_restart_->setRenderPosition(Game::getInstance()->getScreenSize() / 2.0f - glm::vec2(200.f, 0.0f));
    button_restart_->setScale(4.0f);
    button_back_->setRenderPosition(Game::getInstance()->getScreenSize() / 2.0f + glm::vec2(200.f, 0.0f));
    button_back_->setScale(4.0f);
    button_pause_->setActive(false);
    end_timer_->stop();
}

void SceneMain::checkSlowDown(float &dt)
{
    if (Game::getInstance()->getMouseButtons() & SDL_BUTTON_RMASK){
        dt *= 0.4;
    }
}
