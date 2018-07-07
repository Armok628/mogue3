#include "creatures.h"
etype_t player_etype={
	.name="Player",
	.symbol='@',
	.color=LCYAN,
	.maxhp=100,.minhp=50,
	.maxres=15,.minres=5,
	.maxagi=15,.minagi=5,
	.maxwis=15,.minwis=5,
	.maxstr=15,.minstr=5,
	.flags=PERSISTS|SOLID|MOBILE,
	.spells={
		&heal_self_spell,
		&magic_missile_spell,
		&raise_dead_spell,
		&freeze_spell,
		&thaw_spell
	},
	.enemies={
		&monster_etype
	},
	.spawn_flags=NONE
};
etype_t human_etype={
	.name="Human",
	.symbol='U',
	.color=CYAN,
	.maxhp=100,.minhp=50,
	.maxres=15,.minres=5,
	.maxagi=15,.minagi=5,
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
	},
	.spawn_flags=TOWN|INSIDE|OUTSIDE,
	.min_elev=1,.max_elev=100
};
etype_t monster_etype={
	.name="Monster",
	.symbol='&',
	.color=DGRAY,
	.maxhp=100,.minhp=50,
	.maxres=15,.minres=5,
	.maxagi=15,.minagi=5,
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
	},
	.spawn_flags=TOWN|WILDERNESS|DUNGEON|OUTSIDE,
	.min_elev=1,.max_elev=100
};
etype_t frog_etype={
	.name="Frog",
	.symbol='<',
	.color=GREEN,
	.maxhp=10,.minhp=5,
	.maxres=5,.minres=1,
	.maxagi=20,.minagi=15,
	.maxwis=2,.minwis=1,
	.maxstr=5,.minstr=1,
	.flags=SOLID|MOBILE|PERSISTS,
	.friends={
		&frog_etype
	},
	.spawn_flags=WILDERNESS|OUTSIDE,
	.min_elev=51,.max_elev=60
};
