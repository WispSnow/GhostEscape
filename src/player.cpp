#include "player.h"
#include "core/scene.h"
#include "affiliate/sprite_anim.h"
#include "affiliate/collider.h"
#include "raw/stats.h"
#include "affiliate/text_label.h"
#include "raw/timer.h"
#include "move_control_arrow.h"
#include "move_control_wasd.h"

void Player::init()
{
    Actor::init();
    flash_timer_ = Timer::addTimerChild(this, 0.4f);
    flash_timer_->start();
    max_speed_ = 500.0f;
    sprite_idle_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-idle.png", 2.0f);
    sprite_move_ = SpriteAnim::addSpriteAnimChild(this, "assets/sprite/ghost-move.png", 2.0f);
    sprite_move_->setActive(false);

    collider_ = Collider::addColliderChild(this, sprite_idle_->getSize() / 2.0f);
    stats_ = Stats::addStatsChild(this);
    effect_ = Effect::addEffectChild(Game::getInstance().getCurrentScene(), "assets/effect/1764.png", glm::vec2(0), 2.0f);
    effect_->setActive(false);
    weapon_thunder_ = WeaponThunder::addWeaponThunderChild(this, 2.0f, 40.0f);

    move_control_ = new MoveControlWASD();
    addChild(move_control_);
}

bool Player::handleEvents(SDL_Event& event)
{
    if (Actor::handleEvents(event)) return true;
    // 按C键切换WASD，按V键切换箭头
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
        if (event.key.scancode == SDL_SCANCODE_C) setMoveControl(new MoveControlWASD());
        if (event.key.scancode == SDL_SCANCODE_V) setMoveControl(new MoveControlArrow());
        return true;
    }
    return false;
    
}

void Player::update(float dt)
{
    Actor::update(dt);
    velocity_ *= 0.9f;
    moveControl();
    checkState();
    move(dt);
    syncCamera();
    checkIsDead();
}

void Player::render()
{
    if (stats_->getInvincible() && flash_timer_->getProgress() < 0.5f){
        return;
    }
    Actor::render();
}

void Player::clean()
{
    Actor::clean();
}

void Player::takeDamage(float damage)
{
    if (!stats_ || stats_->getInvincible()) return;
    Actor::takeDamage(damage);
    Game::getInstance().playSound("assets/sound/hit-flesh-02-266309.mp3");
}

void Player::setMoveControl(MoveControl *move_control)
{
    if (move_control_ != nullptr) {
        move_control_->setNeedRemove(true);
    }
    move_control_ = move_control;
    safeAddChild(move_control);
}

void Player::moveControl()
{
    if (move_control_ == nullptr) return;
    if (move_control_->isUp()){
        velocity_.y = -max_speed_;
    }
    if (move_control_->isDown()){
        velocity_.y = max_speed_;
    }
    if (move_control_->isLeft()){
        velocity_.x = -max_speed_;
    }
    if (move_control_->isRight()){
        velocity_.x = max_speed_;
    }
}

void Player::syncCamera()
{
    Game::getInstance().getCurrentScene()->setCameraPosition(position_ - Game::getInstance().getScreenSize() / 2.0f);
}

void Player::checkState()
{
    
    if (velocity_.x < 0){
        sprite_move_->setFlip(true);
        sprite_idle_->setFlip(true);
    }else{
        sprite_move_->setFlip(false);
        sprite_idle_->setFlip(false);
    }
    
    bool new_is_moving = (glm::length(velocity_) > 0.1f);
    if (new_is_moving != is_moving_){
        is_moving_ = new_is_moving;
        changeState(is_moving_);
    }
}

void Player::changeState(bool is_moving)
{
    if (is_moving){
        sprite_idle_->setActive(false);
        sprite_move_->setActive(true);
        sprite_move_->setCurrentFrame(sprite_idle_->getCurrentFrame());
        sprite_move_->setFrameTimer(sprite_idle_->getFrameTimer());
        
    }else{
        sprite_idle_->setActive(true);
        sprite_move_->setActive(false);
        sprite_idle_->setCurrentFrame(sprite_move_->getCurrentFrame());
        sprite_idle_->setFrameTimer(sprite_move_->getFrameTimer());
    }
}

void Player::checkIsDead()
{
    if (!stats_->getIsAlive()){
        effect_->setActive(true);
        effect_->setPosition(getPosition());
        setActive(false);
        Game::getInstance().playSound("assets/sound/female-scream-02-89290.mp3");
    }
}