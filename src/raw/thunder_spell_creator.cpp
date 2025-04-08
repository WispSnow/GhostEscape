#include "thunder_spell_creator.h"
#include "../core/scene.h"

Spell *ThunderSpellCreator::createSpell()
{
    return Spell::addSpellChild(Game::getInstance().getCurrentScene(), "assets/effect/Thunderstrike w blur.png", glm::vec2(0), 40.0f, 3.0f);
}
