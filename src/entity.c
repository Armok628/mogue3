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
entity_t *spawn(etype_t *type)
{
	entity_t *e=calloc(1,sizeof(entity_t));
	e->name=type->name;
	e->symbol=type->symbol;
	e->color=type->color;
	e->maxhp=ranged_rand(type->hp);
	e->hp=e->maxhp;
	e->res=ranged_rand(type->res);
	e->agi=ranged_rand(type->agi);
	e->wis=ranged_rand(type->wis);
	e->str=ranged_rand(type->str);
	e->flags=type->flags;
	for (int i=0;type->spells[i];i++)
		e->spells[i]=type->spells[i];
	int n=0;
	ltab_t *lt=&type->loot_table;
	for (int i=0;lt->items[i];i++) {
		if (lt->chances[i]<(rand()%100))
			continue;
		int c=ranged_rand(lt->amounts[i]);
		add_item(e->inventory,lt->items[i],c);
	}
	e->type=type;
	return e;
}
void spawn_randomly(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=empty_coords(area);
	area[e->coords].e=e;
}
void spawn_inside(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=inside_coords(area);
	area[e->coords].e=e;
}
void spawn_outside(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=outside_coords(area);
	area[e->coords].e=e;
}
