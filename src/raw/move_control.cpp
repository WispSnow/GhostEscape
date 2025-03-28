#include "move_control.h"
#include "../core/actor.h"

void MoveControl::update(float dt)
{
    if (parent_ == nullptr) return;
    Object::update(dt);
    parent_->setVelocity(parent_->getVelocity() * 0.9f);
    auto direction = glm::vec2(is_right_ - is_left_, is_down_ - is_up_);
    if (glm::length(direction) > 0.1f) direction = glm::normalize(direction);
    if (glm::length(direction) > 0.1f) parent_->setVelocity(direction * max_speed_);
}

bool MoveControl::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_KEY_DOWN){
        if (event.key.scancode == SDL_SCANCODE_W) is_up_ = true;
        if (event.key.scancode == SDL_SCANCODE_S) is_down_ = true;
        if (event.key.scancode == SDL_SCANCODE_A) is_left_ = true;
        if (event.key.scancode == SDL_SCANCODE_D) is_right_ = true;
        return true;
    }
    if (event.type == SDL_EVENT_KEY_UP){
        if (event.key.scancode == SDL_SCANCODE_W) is_up_ = false;
        if (event.key.scancode == SDL_SCANCODE_S) is_down_ = false;
        if (event.key.scancode == SDL_SCANCODE_A) is_left_ = false;
        if (event.key.scancode == SDL_SCANCODE_D) is_right_ = false;
        return true;
    }
    Object::handleEvents(event);
    return false;
}

// void MoveControl::checkInput()
// {
//     auto keyboard = SDL_GetKeyboardState(NULL);
//     is_up_ = keyboard[SDL_SCANCODE_W];
//     is_down_ = keyboard[SDL_SCANCODE_S];
//     is_left_ = keyboard[SDL_SCANCODE_A];
//     is_right_ = keyboard[SDL_SCANCODE_D];
// }
