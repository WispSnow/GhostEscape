#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "stats.h"
#include "../core/scene.h"
#include "../screen/hud_skill.h"

Weapon *Weapon::addWeaponChild(Actor *parent, float cool_down, float mana_cost)
{
    auto weapon = new Weapon();
    weapon->init();
    weapon->setParent(parent);
    weapon->setCoolDown(cool_down);
    weapon->setManaCost(mana_cost);
    if (parent) parent->addChild(weapon);
    return weapon;
}

bool Weapon::handleEvents(SDL_Event &event)
{
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (event.button.button == trigger_button_) {
            auto pos = Game::getInstance().getMousePosition() + Game::getInstance().getCurrentScene()->getCameraPosition();
            attack(pos);
            return true;
        }
    }
    return false;
}

void Weapon::update(float dt)
{
    Object::update(dt);
    cool_down_timer_ += dt;  // 很可能大于1
    if (hud_skill_) hud_skill_->setPercentage(cool_down_timer_ / cool_down_);   // 应该是0～1的值
}

void Weapon::attack(glm::vec2 position)
{
    if (!spell_prototype_ || !canAttack()) return;
    parent_->getStats()->useMana(mana_cost_);
    cool_down_timer_ = 0.0f;
    // 把spell_prototype_复制一份，添加到场景中
    Game::getInstance().playSound(sound_path_);
    auto spell = spell_prototype_->clone();
    spell->setPosition(position);
}

bool Weapon::canAttack()
{
    if (cool_down_timer_ < cool_down_) return false;
    if (!parent_->getStats()->canUseMana(mana_cost_)) return false;
    return true;
}
