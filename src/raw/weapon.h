#ifndef WEAPON_H
#define WEAPON_H

#include "../core/object.h"
#include "spell_creator.h"

class Spell;
class Actor;
class HUDSkill;
class Weapon : public Object
{
protected:
    Actor* parent_ = nullptr;
    SpellCreator* spell_creator_ = nullptr;
    SDL_MouseButtonFlags trigger_button_ = SDL_BUTTON_LEFT;     // 只能设置为鼠标按键
    HUDSkill* hud_skill_ = nullptr;
    std::string sound_path_ = "assets/sound/big-thunder.mp3";
    float cool_down_ = 1.0f;
    float mana_cost_ = 0.0f;
    float cool_down_timer_ = 0.0f;
public:
    static Weapon* addWeaponChild(Actor* parent, float cool_down, float mana_cost);
    virtual bool handleEvents(SDL_Event& event) override;
    virtual void update(float dt) override;
    
    void attack(glm::vec2 position);
    bool canAttack();
    // getters and setters
    float getCoolDown() const { return cool_down_; }
    void setCoolDown(float cool_down) { cool_down_ = cool_down; }
    float getManaCost() const { return mana_cost_; }
    void setManaCost(float mana_cost) { mana_cost_ = mana_cost; }
    void setParent(Actor* parent) { parent_ = parent; }
    Actor* getParent() const { return parent_; }
    void setSoundPath(const std::string& sound_path) { sound_path_ = sound_path; }

    SDL_MouseButtonFlags getTriggerButton() const { return trigger_button_; }
    void setTriggerButton(SDL_MouseButtonFlags trigger_button) { trigger_button_ = trigger_button; }
    SpellCreator* getSpellCreator() const { return spell_creator_; }
    void setSpellCreator(SpellCreator* spell) { spell_creator_ = spell; }
    HUDSkill* getHUDSkill() const { return hud_skill_; }
    void setHUDSkill(HUDSkill* hud_skill) { hud_skill_ = hud_skill; }
};




#endif // WEAPON_H