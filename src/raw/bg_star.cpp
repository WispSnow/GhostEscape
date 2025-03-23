#include "bg_star.h"
#include "../core/scene.h"

BgStar *BgStar::addBgStarChild(Object *parent, int num, float scale_far, float scale_mid, float scale_near)
{
    BgStar *bg_star = new BgStar();
    bg_star->init();
    bg_star->num_ = num;
    bg_star->scale_far_ = scale_far;
    bg_star->scale_mid_ = scale_mid;
    bg_star->scale_near_ = scale_near;
    bg_star->star_far_.reserve(num);        // 预先把内存分配好，以免后续重新分配
    bg_star->star_mid_.reserve(num);
    bg_star->star_near_.reserve(num);
    auto extra = Game::getInstance()->getCurrentScene()->getWorldSize() - Game::getInstance()->getScreenSize();
    for (auto i = 0; i < num; i++)
    {
        bg_star->star_far_.push_back(Game::getInstance()->randomVec2(glm::vec2(0), Game::getInstance()->getScreenSize() + extra * scale_far));
        bg_star->star_mid_.push_back(Game::getInstance()->randomVec2(glm::vec2(0), Game::getInstance()->getScreenSize() + extra * scale_mid));
        bg_star->star_near_.push_back(Game::getInstance()->randomVec2(glm::vec2(0), Game::getInstance()->getScreenSize() + extra * scale_near));
    }
    if (parent) parent->addChild(bg_star);
    return bg_star;
}

void BgStar::update(float dt)
{
    // 更新颜色
    timer_ += dt;
    color_far_ = {0.5f + 0.5f*sinf(timer_*0.9f), 0.5f + 0.5f*sinf(timer_*0.8f), 0.5f + 0.5f*sinf(timer_*0.7f), 1};
    color_mid_ = {0.5f + 0.5f*sinf(timer_*0.8f), 0.5f + 0.5f*sinf(timer_*0.7f), 0.5f + 0.5f*sinf(timer_*0.6f), 1};
    color_near_ = {0.5f + 0.5f*sinf(timer_*0.7f), 0.5f + 0.5f*sinf(timer_*0.6f), 0.5f + 0.5f*sinf(timer_*0.5f), 1};
}

void BgStar::render()
{
    Game::getInstance()->drawPoints(star_far_, - Game::getInstance()->getCurrentScene()->getCameraPosition() * scale_far_, color_far_);
    Game::getInstance()->drawPoints(star_mid_, - Game::getInstance()->getCurrentScene()->getCameraPosition() * scale_mid_, color_mid_);
    Game::getInstance()->drawPoints(star_near_, - Game::getInstance()->getCurrentScene()->getCameraPosition() * scale_near_, color_near_);
}
