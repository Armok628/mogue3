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
	.value=5,
	.symbol='?',
	.color=LRED,
	.use=&eat_chicken,
	.spawn_flags=NONE,
};
etype_t chicken_etype={
	.name="Chicken",
	.symbol='c',
	.color=YELLOW,
	.hp={10,25},
	.res={1,5},
	.agi={10,15},
	.wis={1,5},
	.str={5,10},
	.flags=SOLID|MOBILE,
	.loot_table={
		.items={&chicken_leg},
		.chances={100},
		.amounts={{2,2}},
	},
	.friends={
		&chicken_etype,
		&human_etype,
	},
	.spawn_flags=TOWN|OUTSIDE,
	.elev={1,65},
	.quota={5,10},
};
