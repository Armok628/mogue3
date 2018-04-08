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
void cast(entity_t *c,int n)
{
	c->spells[n]->function(c);
}
void spell_menu(entity_t *c)
{
	if (!c->spellc)
		return;
	char *strs[c->spellc];
	for (int i=0;i<c->spellc;i++)
		strs[i]=c->spells[i]->name;
	int choice=menu(strs,c->spellc);
	c->spells[choice]->function(c);
}
SPELL_START(heal_self,Heal Self,DEFENSE)
	ON(caster)
	int effect=rand()%caster->wis;
	target->hp+=effect;
	if (target->hp>target->maxhp)
		target->hp=target->maxhp;
	announce("e s d s",caster,"casts Heal Self, gaining",effect,"HP");
SPELL_END
SPELL_START(magic_missile,Magic Missile,OFFENSE)
	ON(local_area[target_by(caster)].e)
	if (!target)
		return;
	int effect=rand()%caster->wis;
	target->hp-=effect;
	if (target->hp<0)
		target->hp=0;
	announce("e s es d s",caster,"casts Magic Missile on",target,", doing",effect,"damage");
	redraw(target);
SPELL_END
SPELL_START(raise_dead,Raise Dead,OFFENSE)
	ON(local_area[target_by(caster)].corpse)
	if (!target)
		return;
	tile_t *t=&local_area[target->coords];
	if (t->fg||t->e)
		return;
	int effect=rand()%caster->wis;
	announce("e s es d s",caster,"casts Raise Dead on",target,", giving",effect,"health");
	target->hp+=effect;
	t->e=target;
	t->corpse=NULL;
	if (target->hp>target->maxhp)
		target->hp=target->maxhp;
	redraw(target);
SPELL_END
