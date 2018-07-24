#include "items.h"
itype_t sword={
	.name="Sword",
	.category=OFFENSE,
	.effect=10,
	.value=100,
	.symbol='/',
	.color=WHITE,
	.spawn_flags=NONE,
};
itype_t gold={
	.name="Gold",
	.category=UTILITY,
	.effect=0,
	.value=1,
	.symbol='$',
	.color=YELLOW,
	.spawn_flags=DUNGEON,
	.freq={100,{5,20},{2,5}},
};
int target_chop(int coords)
{
	int targets[9],count=0;
	for (int dx=-1;dx<=1;dx++)
		for (int dy=-1;dy<=1;dy++) {
			int i=coords+lin(dx,dy);
			if (local_area[i].fg=='|')
				targets[count++]=i;
		}
	return count?targets[rand()%count]-coords:0;
}
void axe_use(entity_t *e)
{
	int o;
	if (e==player)
		o=input_offset(get_input());
	else
		o=target_chop(e->coords);
	if (!o)
		return;
	int t=e->coords+o;
	if (local_area[t].fg!='|'||local_area[t].fg_c!=BROWN)
		return;
	local_area[t].fg='\0';
	add_item(local_area[t].pile,&lumber,1);
	announce("e s",e,"chops down a tree");
	if (!(rand()%10)) {
		printf(", breaking the axe");
		remove_item(e->inventory,&axe,1);
	}
	draw_posl(t);
}
itype_t axe={
	.name="Axe",
	.category=OFFENSE,
	.effect=5,
	.value=50,
	.symbol='P',
	.color=WHITE,
	.use=&axe_use,
	.spawn_flags=TOWN|INSIDE,
	.elev={1,100},
	.freq={50,{1,1},{1,1}},
};
itype_t raft={
	.name="Raft",
	.category=UTILITY,
	.effect=0,
	.value=20,
	.symbol='#',
	.color=BROWN,
	.spawn_flags=NONE,
};
void lumber_use(entity_t *e)
{
	if (e!=player)
		return;
	if (!item_count(e->inventory,&axe)) {
		announce("s","You need an axe to build");
		return;
	}
	static char *opts[]={"Floor","Wall"};
	int c=menu(opts,2);
	int t=e->coords+input_offset(get_input());
	if (t==e->coords)
		return;
	switch (c) {
	case 0: // Floor
		local_area[t].bg='#';
		local_area[t].bg_c=BROWN;
		break;
	case 1: // Wall
		if (local_area[t].bg!='#') {
			announce("s","There must be a floor first");
			return;
		}
		local_area[t].fg='%';
		local_area[t].fg_c=BROWN;
		break;
	default:
		return;
	}
	draw_posl(t);
	remove_item(e->inventory,&lumber,1);
}
itype_t lumber={
	.name="Log",
	.category=UTILITY,
	.effect=0,
	.value=5,
	.symbol='=',
	.color=BROWN,
	.use=&lumber_use,
	.spawn_flags=WILDERNESS|TOWN|OUTSIDE,
	.elev={51,60},
	.freq={100,{1,1},{1,5}},
};
itype_t rock={
	.name="Rock",
	.category=UTILITY,
	.effect=0,
	.value=0,
	.symbol='*', // How to distinguish from ground texture?
	.color=D_GRAY,
	.spawn_flags=NONE,//WILDERNESS|TOWN|OUTSIDE,
	.elev={1,100},
	.freq={100,{1,2},{2,5}},
};
itype_t scepter={
	.name="Scepter",
	.category=UTILITY,
	.effect=0,
	.value=1000,
	.symbol='I',
	.color=PURPLE,
	.use=&raise_dead,
	.spawn_flags=DUNGEON,
	.freq={25,{1,1},{1,1}},
};
void eat_poison_apple(entity_t *e)
{
	announce("e s",e,"eats a poison apple");
	remove_item(e->inventory,&poison_apple,1);
	kill_entity(e);
	draw_posl(e->coords);
}
itype_t poison_apple={
	.name="Poison Apple",
	.category=UTILITY,
	.effect=0,
	.value=0,
	.symbol='o',
	.color=RED,
	.use=&eat_poison_apple,
	.spawn_flags=DUNGEON,
	.freq={50,{1,1},{1,2}},
};
