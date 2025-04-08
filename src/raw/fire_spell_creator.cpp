#include "fire_spell_creator.h"
#include "../core/scene.h"

Spell *FireSpellCreator::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(), "assets/effect/Explosion 2 SpriteSheet.png", glm::vec2(0), 20.0f, 3.0f);
}