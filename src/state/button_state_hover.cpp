#include "button_state_hover.h"
#include "button_state_normal.h"
#include "button_state_press.h"

void ButtonStateHover::onEnter() {
    Game::getInstance().playSound("assets/sound/UI_button12.wav");
    parent_->getSpriteHover()->setActive(true);
}

void ButtonStateHover::onExit() {
    parent_->getSpriteHover()->setActive(false);
}

bool ButtonStateHover::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
        auto size = parent_->getSpriteNormal()->getSize();
        if (!Game::getInstance().isMouseInRect(pos, pos + size)){
            parent_->changeState(new ButtonStateNormal());
            return true;
        }
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            parent_->changeState(new ButtonStatePress());
            return true;
        }
    }
    return false;
}