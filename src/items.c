#include "items.h"
int chop_target(int coords)
{
	int targets[9],count;
	for (int dx=-1;dx<=1;dx++)
		for (int dy=-1;dy<=1;dy++) {
			int i=coords+lin(dx,dy);
			if (local_area[i].fg=='|')
				targets[count++]=i;
		}
	return count?targets[rand()%count]:0;
}
void axe_use(entity_t *e)
{
	int o;
	if (e==player)
		o=input_offset(fgetc(stdin));
	else
		o=chop_target(e->coords);
	if (!o)
		return;
	int t=e->coords+o;
	if (local_area[t].fg=='|'&&local_area[t].fg_c==BROWN) {
		local_area[t].fg='\0';
		add_item(local_area[t].pile,&lumber,1);
	}
	draw_posl(t);
}
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
};
itype_t axe={
	.name="Axe",
	.category=OFFENSE,
	.effect=5,
	.value=50,
	.symbol='P',
	.color=WHITE,
	.use=&axe_use,
	.spawn_flags=TOWN|INSIDE,
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
itype_t lumber={
	.name="Log",
	.category=UTILITY,
	.effect=0,
	.value=5,
	.symbol='=',
	.color=BROWN,
	.spawn_flags=WILDERNESS|TOWN|OUTSIDE,
};
itype_t rock={
	.name="Rock",
	.category=UTILITY,
	.effect=0,
	.value=0,
	.symbol='*',
	.color=DGRAY,
	.spawn_flags=WILDERNESS|TOWN|OUTSIDE,
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
};
