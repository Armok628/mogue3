#include "entity.h"
entity_t *player;
void draw_entity(entity_t *e)
{
	set_color(e->color,e->hp?BG BLACK:BG RED);
	putchar(e->symbol);
}
static inline int rand_in_range(int min,int max)
{
	return min+rand()%(max-min);
}
void transform(entity_t *e,etype_t *type)
{
	e->flags=type->flags;
	if (e->flags&PERSISTS) {
		if (e->name)
			free(e->name);
		e->name=random_word(4+rand()%4);
		e->name[0]+='A'-'a';
	} else
		e->name=type->name;
	e->symbol=type->symbol;
	e->color=type->color;
	e->maxhp=ranged_rand(type->hp);
	e->hp=e->maxhp;
	e->res=ranged_rand(type->res);
	e->agi=ranged_rand(type->agi);
	e->wis=ranged_rand(type->wis);
	e->str=ranged_rand(type->str);
	for (int i=0;type->spells[i];i++)
		e->spells[i]=type->spells[i];
	int n=0;
	ltab_t *lt=&type->loot_table;
	for (int i=0;(*lt)[i].type;i++) {
		if ((*lt)[i].freq.chance<(rand()%100))
			continue;
		int c=ranged_rand((*lt)[i].freq.counts);
		add_item(e->inventory,(*lt)[i].type,c);
	}
	e->type=type;
}
entity_t *spawn(etype_t *type)
{
	entity_t *e=calloc(1,sizeof(entity_t));
	transform(e,type);
	return e;
}
void init_perm_effects(entity_t *ent)
{
	int c=ent->coords;
	eslot_t *e=ent->effects;
	effect_t **t=ent->type->perm_effects;
	for (int i=0;t[i];i++)
		add_effect(e,t[i],-1,c);
}
void spawn_at(tile_t *area,int c,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=c;
	area[c].e=e;
	init_perm_effects(e);
}
void spawn_randomly(tile_t *area,etype_t *type)
{
	spawn_at(area,empty_coords(area),type);
}
void spawn_inside(tile_t *area,etype_t *type)
{
	spawn_at(area,inside_coords(area),type);
}
void spawn_outside(tile_t *area,etype_t *type)
{
	spawn_at(area,outside_coords(area),type);
}
