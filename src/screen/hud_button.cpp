#include "hud_button.h"
#include "../state/button_state.h"
#include "../state/button_state_normal.h"

HUDButton *HUDButton::addHUDButtonChild(Object *parent, glm::vec2 render_pos, const std::string &file_path1, const std::string &file_path2, const std::string &file_path3, float scale, Anchor anchor)
{
    auto hud_button = new HUDButton();
    hud_button->init();
    hud_button->setRenderPosition(render_pos);
    hud_button->sprite_normal_ = Sprite::addSpriteChild(hud_button, file_path1, scale, anchor);
    hud_button->sprite_hover_ = Sprite::addSpriteChild(hud_button, file_path2, scale, anchor);
    hud_button->sprite_press_ = Sprite::addSpriteChild(hud_button, file_path3, scale, anchor);
    hud_button->sprite_hover_->setActive(false);
    hud_button->sprite_press_->setActive(false);
    hud_button->changeState(new ButtonStateNormal());
    if (parent) parent->addChild(hud_button);
    return hud_button;
}

void HUDButton::changeState(ButtonState *button_state)
{
    if (button_state_) {
        button_state_->onExit();
        button_state_->setNeedRemove(true);
    }
    if (!button_state) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "button_state is nullptr");
        return;
    }
    button_state_ = button_state;
    button_state_->init();
    button_state_->setParent(this);
    button_state_->onEnter();
    safeAddChild(button_state_);
}

bool HUDButton::getIsTrigger()
{
    if (is_trigger_){
        is_trigger_ = false;
        return true;
    }
    return false;
}

void HUDButton::setScale(float scale)
{
    sprite_normal_->setScale(scale);
    sprite_hover_->setScale(scale);
    sprite_press_->setScale(scale);
}
