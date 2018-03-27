#include "spells.h"
/*
void heal_self(entity_t *caster);
spell_t heal_self_spell={
	.function=&heal_self,
	.name="Heal Self",
	.type=DEFENSE
};
void heal_self(entity_t *caster)
{
	entity_t *target=caster;
	int effect=caster->wis; // Temporary
	target->hp+=effect;
	announce("e s d s",caster,"casts Heal Self, gaining",effect,"HP");
}
*/
SPELL_START(heal_self,Heal Self,DEFENSE) ON(caster)
	int effect=rand()%caster->wis;
	target->hp+=effect;
	announce("e s d s",caster,"casts Heal Self, gaining",effect,"HP");
SPELL_END
