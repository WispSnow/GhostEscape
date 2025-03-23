#include "spawner.h"
#include "enemy.h"
#include "world/effect.h"
#include "core/scene.h"

void Spawner::update(float dt)
{
    if (!target_ || !target_->getActive()) return;
    timer_ += dt;
    if (timer_ >= interval_)
    {
        timer_ = 0;
        Game::getInstance()->playSound("assets/sound/silly-ghost-sound-242342.mp3");
        for (int i = 0; i < num_; i++)
        {
            // spawn enemy
            auto pos = Game::getInstance()->randomVec2(Game::getInstance()->getCurrentScene()->getCameraPosition(), Game::getInstance()->getCurrentScene()->getCameraPosition() + Game::getInstance()->getScreenSize());
            Enemy* enemy = Enemy::addEnemyChild(nullptr, pos, target_);
            Effect::addEffectChild(Game::getInstance()->getCurrentScene(), "assets/effect/184_3.png", pos, 1.0f, enemy);
        }
    }
}
