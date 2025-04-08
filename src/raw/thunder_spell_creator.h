#ifndef THUNDER_SPELL_CREATOR_H
#define THUNDER_SPELL_CREATOR_H

#include "spell_creator.h"

class ThunderSpellCreator : public SpellCreator {
public:
    Spell* createSpell() override;
};

#endif // THUNDER_SPELL_CREATOR_H
