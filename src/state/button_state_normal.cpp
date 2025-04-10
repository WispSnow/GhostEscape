#include "button_state_normal.h"
#include "button_state_hover.h"

void ButtonStateNormal::onEnter()
{
    parent_->getSpriteNormal()->setActive(true);
}

void ButtonStateNormal::onExit()
{
    parent_->getSpriteNormal()->setActive(false);
}

bool ButtonStateNormal::handleEvents(SDL_Event& event)
{
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
        auto pos = parent_->getRenderPosition() + parent_->getSpriteNormal()->getOffset();
        auto size = parent_->getSpriteNormal()->getSize();
        if (Game::getInstance().isMouseInRect(pos, pos + size)){
            parent_->changeState(new ButtonStateHover());
            return true;
        }
    }
    return false;
}