#include "button_state_press.h"
#include "button_state_normal.h"

void ButtonStatePress::onEnter() {
    Game::getInstance().playSound("assets/sound/UI_button08.wav");
    parent_->getSpritePress()->setActive(true);
}

void ButtonStatePress::onExit() {
    parent_->getSpritePress()->setActive(false);
}

bool ButtonStatePress::handleEvents(SDL_Event& event) {
    if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
            auto size = parent_->getSpriteNormal()->getSize();
            if (Game::getInstance().isMouseInRect(pos, pos + size)){
                parent_->setIsTrigger(true);
            }
            parent_->changeState(new ButtonStateNormal());
            return true;
        }
    }
    return false;
}