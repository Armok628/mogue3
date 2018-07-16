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
	if (!(rand()%20)&&c->wis<20) {
		announce("e s",c,"is now wiser from it");
		c->wis++;
	}
}
void spell_menu(entity_t *e)
{
	char *names[16];
	int c=0;
	for (;e->spells[c];c++)
		names[c]=e->spells[c]->name;
	int choice=menu(names,c);
	if (choice<0)
		return;
	cast(e,choice);
}
void random_spell(entity_t *e)
{
	int n=0;
	for (;e->spells[n];n++);
	if (!n)
		return;
	cast(e,rand()%n);
}
SPELL_START(heal_self,Heal Self,DEFENSE)
	ON(caster)
	if (caster->hp==caster->maxhp)
		return;
	int effect=rand()%caster->wis;
	target->hp+=effect;
	if (target->hp>target->maxhp)
		target->hp=target->maxhp;
	announce("e s d s",caster,"casts Heal Self, gaining",effect,"HP");
SPELL_END
SPELL_START(magic_missile,Magic Missile,OFFENSE)
	ON(target_enemy(caster))
	if (!target)
		return;
	int effect=rand()%caster->wis;
	announce("e s es d s",caster,"casts Magic Missile on",target,", doing",effect,"damage");
	target->hp-=effect;
	if (target->hp<=0) {
		target->hp=0;
		kill_entity(target);
	}
	draw_posl(target->coords);
SPELL_END
SPELL_START(raise_dead,Raise Dead,DEFENSE)
	ON(target_corpse(caster))
	if (!target)
		return;
	tile_t *t=&local_area[target->coords];
	if (t->fg||t->e)
		return;
	int effect=rand()%caster->wis;
	announce("e s es d s",caster,"casts Raise Dead on",target,", giving",effect,"health");
	if (!effect)
		return;
	target->hp+=effect;
	t->e=target;
	t->corpse=NULL;
	if (target->hp>target->maxhp)
		target->hp=target->maxhp;
	draw_posl(target->coords);
SPELL_END
SPELL_START(freeze,Freeze,OFFENSE)
	ON(target_enemy(caster))
	if (!target)
		return;
	target->color=WHITE;
	target->flags&=~MOBILE;
	draw_posl(target->coords);
SPELL_END
SPELL_START(thaw,Thaw,DEFENSE)
	ON(target_friend(caster))
	if (!target)
		return;
	target->color=target->type->color;
	target->flags|=MOBILE;
	draw_posl(target->coords);
SPELL_END
SPELL_START(dragonfire,Dragonfire,OFFENSE)
	ON(target_enemy(caster))
	if (!target)
		return;
	int effect=10+rand()%caster->wis;
	announce("e s es d s",caster,"breathes fire at",target,", doing",effect,"damage");
	target->hp-=effect;
	if (target->hp<=0) {
		target->hp=0;
		kill_entity(target);
	}
	draw_posl(target->coords);
SPELL_END
