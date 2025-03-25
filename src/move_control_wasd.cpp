#include "move_control_wasd.h"

void MoveControlWASD::update(float dt)
{
    MoveControl::update(dt);
    auto keyboard = SDL_GetKeyboardState(NULL);
    is_up_ = keyboard[SDL_SCANCODE_W];
    is_down_ = keyboard[SDL_SCANCODE_S];
    is_left_ = keyboard[SDL_SCANCODE_A];
    is_right_ = keyboard[SDL_SCANCODE_D];
}
