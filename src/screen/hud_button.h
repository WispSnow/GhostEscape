#ifndef HUD_BUTTON_H
#define HUD_BUTTON_H

#include "../core/object_screen.h"
#include "../affiliate/sprite.h"

class ButtonState;
class HUDButton : public ObjectScreen 
{
protected:
    Sprite* sprite_normal_ = nullptr;
    Sprite* sprite_hover_ = nullptr;
    Sprite* sprite_press_ = nullptr;

    ButtonState* button_state_ = nullptr;

    bool is_trigger_ = false;
public:
    static HUDButton* addHUDButtonChild(Object* parent, glm::vec2 render_pos, const std::string& file_path1, const std::string& file_path2, const std::string& file_path3, float scale = 1.0f, Anchor anchor = Anchor::CENTER);

    void changeState(ButtonState* button_state);

    // setters and getters
    Sprite* getSpriteNormal() const { return sprite_normal_; }
    Sprite* getSpriteHover() const { return sprite_hover_; }
    Sprite* getSpritePress() const { return sprite_press_; }

    bool getIsTrigger();   // 只要触发一次，就会重置is_trigger_状态
    void setIsTrigger(bool is_trigger) { is_trigger_ = is_trigger; }
    void setScale(float scale);
};

#endif // HUD_BUTTON_H
