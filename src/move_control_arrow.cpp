#include "move_control_arrow.h"

void MoveControlArrow::update(float dt)
{
    MoveControl::update(dt);
    auto keyboard = SDL_GetKeyboardState(NULL);
    is_up_ = keyboard[SDL_SCANCODE_UP];
    is_down_ = keyboard[SDL_SCANCODE_DOWN];
    is_left_ = keyboard[SDL_SCANCODE_LEFT];
    is_right_ = keyboard[SDL_SCANCODE_RIGHT];
    
}
