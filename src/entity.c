#include "entity.h"
etype_t playertype={
	.name="Player",
	.symbol='@',
	.color=LBLUE,
	.maxhp=100,.minhp=50,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5
};
etype_t monstertype={ // Temporary
	.name="Monster",
	.symbol='&',
	.color=DGRAY,
	.maxhp=100,.minhp=50,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5
};
entity_t *player;
void draw_entity(entity_t *c)
{
	set_color(c->color,c->hp>0?BG BLACK:BG RED);
	putchar(c->symbol);
}
entity_t *make_entity(etype_t *type)
{
	entity_t *e=malloc(sizeof(entity_t));
	e->name=type->name;
	e->symbol=type->symbol;
	e->color=type->color;
	e->maxhp=rand()%(type->maxhp-type->minhp)+type->minhp;
	e->hp=e->maxhp;
	e->str=rand()%(type->maxstr-type->minstr)+type->minstr;
	e->wis=rand()%(type->maxwis-type->minwis)+type->minwis;
	e->spellc=0; // To-do: Spells given to certain creatures?
	return e;
}
entity_t *place_randomly(etype_t *type)
{
	entity_t *e=make_entity(type);
	e->coord=rand()%AREA;
	area[e->coord].e=e;
	return e;
}
void cast(entity_t *c,int n)
{
	c->spells[n](c);
}
