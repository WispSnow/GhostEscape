#include "ui_mouse.h"

UIMouse *UIMouse::addUIMouseChild(Object *parent, const std::string &file_path1, const std::string &file_path2, float scale, Anchor anchor)
{
    auto ui_mouse = new UIMouse();
    ui_mouse->init();
    ui_mouse->sprite1_ = Sprite::addSpriteChild(ui_mouse, file_path1, scale, anchor);
    ui_mouse->sprite2_ = Sprite::addSpriteChild(ui_mouse, file_path2, scale, anchor);
    if (parent) parent->addChild(ui_mouse);
    return ui_mouse;
}

void UIMouse::update(float dt)
{
    timer_ += dt;
    if (timer_ < 0.3f) {
        sprite1_->setActive(true);
        sprite2_->setActive(false);
    } else if (timer_ < 0.6f) {
        sprite1_->setActive(false);
        sprite2_->setActive(true);
    } else {
        timer_ = 0;
    }
    setRenderPosition(Game::getInstance()->getMousePosition());
}
