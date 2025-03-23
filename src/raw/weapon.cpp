#include "weapon.h"
#include "../core/actor.h"
#include "../world/spell.h"
#include "stats.h"
#include "../core/scene.h"

void Weapon::update(float dt)
{
    Object::update(dt);
    cool_down_timer_ += dt;  // 很可能大于1
}

void Weapon::attack(glm::vec2 position, Spell* spell)
{
    if (spell == nullptr) return;
    parent_->getStats()->useMana(mana_cost_);
    cool_down_timer_ = 0.0f;
    spell->setPosition(position);
    Game::getInstance().getCurrentScene()->safeAddChild(spell);
}

bool Weapon::canAttack()
{
    if (cool_down_timer_ < cool_down_) return false;
    if (!parent_->getStats()->canUseMana(mana_cost_)) return false;
    return true;
}
