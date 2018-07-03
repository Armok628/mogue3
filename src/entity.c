#include "entity.h"
etype_t player_etype={
	.name="Player",
	.symbol='@',
	.color=LCYAN,
	.maxhp=100,.minhp=50,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5,
	.flags=PERSISTS|SOLID|MOBILE,
	.spells={
		&heal_self_spell,
		&magic_missile_spell,
		&raise_dead_spell,
		&freeze_spell,
		&thaw_spell
	}
};
etype_t human_etype={ // Temporary
	.name="Human",
	.symbol='U',
	.color=CYAN,
	.maxhp=100,.minhp=50,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5,
	.flags=PERSISTS|SOLID|MOBILE,
	.loot_table={
		.items={&sword,&gold},
		.amounts={1,10},
		.chances={50,100}
	},
	.spells={
		&heal_self_spell
	},
	.friends={
		&human_etype,
		&player_etype
	},
	.enemies={
		&human_etype,
		&player_etype,
		&monster_etype
	}
};
etype_t monster_etype={ // Temporary
	.name="Monster",
	.symbol='&',
	.color=DGRAY,
	.maxhp=100,.minhp=50,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5,
	.flags=SOLID|MOBILE,
	.loot_table={
		.items={&gold},
		.amounts={25},
		.chances={50}
	},
	.spells={
		&magic_missile_spell
	},
	.friends={
		&monster_etype
	},
	.enemies={
		&player_etype,
		&human_etype
	}
};
entity_t *player;
void draw_entity(entity_t *e)
{
	set_color(e->color,e->hp?BG BLACK:BG RED);
	putchar(e->symbol);
}
void redraw(entity_t *e)
{
	int c=e->coords;
	move_cursor(xcmp(c),ycmp(c));
	draw_entity(e);
}
entity_t *spawn(etype_t *type)
{
	entity_t *e=calloc(1,sizeof(entity_t));
	e->name=type->name;
	e->symbol=type->symbol;
	e->color=type->color;
	e->maxhp=rand()%(type->maxhp-type->minhp)+type->minhp;
	e->hp=e->maxhp;
	e->str=rand()%(type->maxstr-type->minstr)+type->minstr;
	e->wis=rand()%(type->maxwis-type->minwis)+type->minwis;
	e->flags=type->flags;
	for (int i=0;type->spells[i];i++)
		e->spells[i]=type->spells[i];
	int n=0;
	ltab_t *lt=&type->loot_table;
	for (int i=0;lt->items[i];i++) {
		int c=1+rand()%lt->amounts[i];
		if (!c||lt->chances[i]<(rand()%100))
			continue;
		e->inventory[n].type=lt->items[i];
		e->inventory[n++].count=c;
	}
	e->type=type;
	return e;
}
entity_t *spawn_randomly(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=empty_coords(area);
	area[e->coords].e=e;
	return e;
}
entity_t *spawn_inside(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=inside_coords(area);
	area[e->coords].e=e;
	return e;
}
entity_t *spawn_outside(tile_t *area,etype_t *type)
{
	entity_t *e=spawn(type);
	e->coords=outside_coords(area);
	area[e->coords].e=e;
	return e;
}
