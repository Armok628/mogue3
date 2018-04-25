#include "items.h"
bool has_axe=false;
bool has_raft=false;
bool has_canoe=false;
int logs=0;
int rocks=0;
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
	.color=LGRAY
};

int select_item(islot_t l[])
{
	char *strs[16];
	int c=0;
	for (;l[c].count;c++)
		strs[c]=l[c].type->name;
	return menu(strs,c);
}
void add_item(islot_t p[],itype_t *t)
{
	int c=0;
	for (;p[c].count;c++)
		if (p[c].type==t) {
			p[c].count++;
			return;
		}
	p[c].type=t;
	p[c].count=1;
}
itype_t *remove_item(islot_t p[],int i)
{
	if (i<0)
		return NULL;
	int c=0;
	for (;p[c].count;c++);
	if (!c)
		return 0;
	islot_t slot=p[i];
	p[i]=p[c-1];
	p[c-1].count=0;
	return slot.type;
}
void remove_type(islot_t p[],itype_t *t)
{
	for (int i=0;p[i].count;i++)
		if (p[i].type==t) {
			remove_item(p,i);
			return;
		}
}
void drop_item(entity_t *e,int i)
{
	if (i<0)
		return;
	tile_t *t=&local_area[e->coords];
	add_item(t->pile,remove_item(e->inventory,i));
}
void drop_menu(entity_t *e)
{
	drop_item(e,select_item(e->inventory));
}
void loot_item(entity_t *e,int i)
{
	if (i<0)
		return;
	tile_t *t=&local_area[e->coords];
	add_item(e->inventory,remove_item(t->corpse->inventory,i));
}
void grab_item(entity_t *e,int i)
{
	if (i<0)
		return;
	tile_t *t=&local_area[e->coords];
	add_item(e->inventory,remove_item(t->pile,i));
}
static char *piles[]={"Corpse","Pile"};
void grab_menu(entity_t *e)
{
	tile_t *t=&local_area[e->coords];
	if (t->pile[0].count&&t->corpse) {
		switch (menu(piles,2)) {
		case 0: // Corpse
			loot_item(e,select_item(t->corpse->inventory));
			return;
		case 1: // Pile
			grab_item(e,select_item(t->pile));
			return;
		}
	} else if (t->corpse) {
		loot_item(e,select_item(t->corpse->inventory));
	} else if (t->pile[0].count) { // anything on ground
		grab_item(e,select_item(t->pile));
	}
}
void equip(entity_t *e,int i)
{
	if (i<0)
		return;
	add_item(e->equipped,remove_item(e->inventory,i));
}
void equip_menu(entity_t *e)
{
	equip(e,select_item(e->inventory));
}
void unequip(entity_t *e,int i)
{
	if (i<0)
		return;
	add_item(e->inventory,remove_item(e->equipped,i));
}
void unequip_menu(entity_t *e)
{
	unequip(e,select_item(e->equipped));
}
bool equipped(entity_t *e,itype_t *t)
{
	for (int i=0;e->equipped[i].count;i++)
		if (e->equipped[i].type==t)
			return true;
	return false;
}
