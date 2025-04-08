#ifndef FIRE_SPELL_CREATOR_H
#define FIRE_SPELL_CREATOR_H

#include "spell_creator.h"

class FireSpellCreator : public SpellCreator {
public:
    Spell* createSpell() override;
};

#endif // FIRE_SPELL_CREATOR_H
