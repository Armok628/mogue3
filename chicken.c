#include "src/creatures.h"
// Add-on example
void eat_chicken(entity_t *e)
{
	announce("e s",e,"eats a leg of chicken");
	e->hp+=10;
	if (e->hp>e->maxhp)
		e->hp=e->maxhp;
	remove_item(e->inventory,&chicken_leg,1);
}
itype_t chicken_leg={
	.name="Chicken Leg",
	.category=UTILITY,
	.effect=0,
	.value=10,
	.symbol='?',
	.color=L_RED,
	.use=&eat_chicken,
	.spawn_flags=NONE,
};
void eat_egg(entity_t *e)
{
	announce("e s",e,"eats an egg");
	e->hp+=5;
	if (e->hp>e->maxhp)
		e->hp=e->maxhp;
	remove_item(e->inventory,&egg,1);
}
itype_t egg={
	.name="Egg",
	.category=UTILITY,
	.effect=0,
	.value=5,
	.symbol='o',
	.color=WHITE,
	.use=&eat_egg,
	.spawn_flags=NONE,
};
void hatch_chick(entity_t *e)
{
	char dir=alt_dir(e->coords,'0'+1+rand()%9);
	int t=e->coords+input_offset(dir);
	spawn_at(local_area,&chick_etype,t);
	announce("e s",e,"hatches a chick from an egg");
	remove_item(e->inventory,&fert_egg,1);
}
itype_t fert_egg={
	.name="Fertilized Egg",
	.category=UTILITY,
	.effect=0,
	.value=15,
	.symbol='o',
	.color=WHITE,
	.use=&hatch_chick,
	.spawn_flags=NONE,
};
bool rooster_visible(int coords)
{
	for (int i=0;i<AREA;i++) {
		tile_t *t=&local_area[i];
		if (t->e&&t->e->type==&rooster_etype&&visible(coords,i))
			return true;
	}
	return false;
}
void lay_egg(int coords)
{
	entity_t *e=local_area[coords].e;
	if (!(rand()%200)) {
		itype_t *eggtype;
		if (rooster_visible(coords))
			eggtype=rand()%4?&egg:&fert_egg;
		else
			eggtype=&egg;
		add_item(local_area[coords].pile,eggtype,1);
		announce("e s",e,"lays an egg");
	}
}
effect_t egg_layer={
	.start=NULL,
	.turn=&lay_egg,
	.end=NULL,
};
etype_t hen_etype={
	.name="Hen",
	.symbol='H',
	.color=BROWN,
	.hp={10,25},
	.res={1,5},
	.agi={10,15},
	.wis={1,5},
	.str={5,10},
	.flags=SOLID|MOBILE|PERSISTS,
	.loot_table={
		{&chicken_leg,{100,{2,2}}},
	},
	.friends={
		&hen_etype,
		&rooster_etype,
		&chick_etype,
		&human_etype,
	},
	.spawn_flags=TOWN|OUTSIDE,
	.elev={51,60},
	.freq={100,{5,10}},
	.perm_effects={&egg_layer},
};
etype_t rooster_etype={
	.name="Rooster",
	.symbol='R',
	.color=RED,
	.hp={20,30},
	.res={5,10},
	.agi={10,15},
	.wis={1,5},
	.str={5,10},
	.flags=SOLID|MOBILE|PERSISTS,
	.loot_table={
		{&chicken_leg,{100,{2,2}}},
	},
	.friends={
		&hen_etype,
		&chick_etype,
	},
	.enemies={
		&rooster_etype,
		&monster_etype,
	},
	.spawn_flags=TOWN|OUTSIDE,
	.elev={51,60},
	.freq={100,{1,5}},
};
void chick_timer(int c)
{
	// They can only have one effect this early
	entity_t *e=local_area[c].e;
	e->effects[0].dur=50+rand()%25;
}
void chick_grow(int c)
{
	entity_t *e=local_area[c].e;
	transform(e,rand()%2?&hen_etype:&rooster_etype);
	init_perm_effects(e);
}
effect_t growing_chick={
	.start=&chick_timer,
	.turn=NULL,
	.end=&chick_grow,
};
etype_t chick_etype={
	.name="Chick",
	.symbol='c',
	.color=YELLOW,
	.hp={5,10},
	.res={1,1},
	.agi={5,10},
	.wis={1,2},
	.str={1,2},
	.flags=SOLID|MOBILE|PERSISTS,
	.friends={
		&hen_etype,
		&rooster_etype,
		&chick_etype,
		&human_etype,
	},
	.spawn_flags=NONE,
	.perm_effects={&growing_chick},
};
