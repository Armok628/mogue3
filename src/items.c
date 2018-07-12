#include "items.h"
void axe_use(entity_t *e)
{ // One can assume only the player can use this for now
	int o=input_offset(fgetc(stdin));
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
	.color=DGRAY
};
itype_t gold={
	.name="Gold",
	.category=UTILITY,
	.effect=0,
	.value=1,
	.symbol='$',
	.color=YELLOW
};
itype_t axe={
	.name="Axe",
	.category=OFFENSE,
	.effect=5,
	.value=50,
	.symbol='P',
	.color=WHITE,
	.use=&axe_use
};
itype_t raft={
	.name="Raft",
	.category=UTILITY,
	.effect=0,
	.value=20,
	.symbol='#',
	.color=BROWN
};
itype_t lumber={
	.name="Log",
	.category=UTILITY,
	.effect=0,
	.value=5,
	.symbol='=',
	.color=BROWN
};
itype_t rock={
	.name="Rock",
	.category=UTILITY,
	.effect=0,
	.value=0,
	.symbol='*',
	.color=DGRAY
};
