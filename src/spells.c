#include "spells.h"
SPELL_START(heal_self,Heal Self) ON(caster)
	int effect=rand()%caster->wis;
	target->hp+=effect;
	announce("esds",caster," casts Heal Self, gaining ",effect," HP");
SPELL_END
