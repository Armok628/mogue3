#include "inventory.h"
int item_menu(islot_t l[])
{ // Returns index of selected item
	static char buf[1000];
	char *strs[16];
	int c=0,b=0;
	for (;l[c].count;c++) {
		if (l[c].count>1)
			sprintf(buf+b,"%s (%d)",l[c].type->name,l[c].count);
		else
			sprintf(buf+b,"%s",l[c].type->name);
		strs[c]=buf+b;
		b+=strlen(buf+b)+1;
	}
	return menu(strs,c);
}
int find_slot(islot_t inv[],itype_t *t)
{ // Returns index of sought slot
	for (int s=0;inv[s].count;s++)
		if (inv[s].type==t)
			return s;
	return -1;
}
int add_slot(islot_t inv[],itype_t *t)
{ // Returns index of added slot
	int s=0;
	for (;inv[s].count;s++);
	if (s==INV_SIZE)
		return 0;
	inv[s].type=t;
	return s;
}
int add_item(islot_t inv[],itype_t *t,int c)
{ // Returns item count added
	if (!c)
		return 0;
	int s=find_slot(inv,t);
	if (s>-1) {
		inv[s].count+=c;
		return c;
	}
	for (s=0;inv[s].count;s++);
	inv[add_slot(inv,t)].count=c;
	return c;
}
int item_count(islot_t inv[],itype_t *t)
{ // Returns item count found
	int s=find_slot(inv,t);
	if (s<0)
		return 0;
	return inv[s].count;
}
void remove_slot(islot_t p[],int s)
{
	if (s<0)
		return;
	int c=0;
	for (;p[c].count;c++);
	if (c<=s)
		return;
	p[s]=p[c-1];
	p[c-1].type=NULL;
	p[c-1].count=0;
}
int remove_item(islot_t inv[],itype_t *t,int c)
{ // Returns true for success and the opposite
	int s=find_slot(inv,t);
	if (s<0)
		return 0;
	else if (c>inv[s].count) {
		return 0;
	} else if (c==inv[s].count) {
		remove_slot(inv,s);
	} else
		inv[s].count-=c;
	return c;
}
void use_menu(entity_t *e)
{
	announce("s","Select an item to use");
	int selection=item_menu(e->inventory);
	if (selection<0)
		return;
	itype_t *t=e->inventory[selection].type;
	if (!t->use)
		announce("s","There's nothing to do with it");
	else
		t->use(e);
}
bool equipped(entity_t *e,itype_t *t)
{
	return item_count(e->equipped,t)>0;
}
void drop_menu(entity_t *e)
	ITEM_MOVE_MENU(e->inventory,local_area[e->coords].pile)
void equip_menu(entity_t *e)
	ITEM_MOVE_MENU(e->inventory,e->equipped)
void unequip_menu(entity_t *e)
	ITEM_MOVE_MENU(e->equipped,e->inventory)
void grab_menu(entity_t *e)
{
	static char *piles[]={"Corpse","Pile"};
	tile_t *t=&local_area[e->coords];
	if (t->corpse&&t->pile[0].count)
		switch (menu(piles,2)) {
		case 0:
			goto GRAB_FROM_CORPSE;
		case 1:
			goto GRAB_FROM_PILE;
		case 2:
			return;
		}
	if (t->corpse)
		goto GRAB_FROM_CORPSE;
	else if (t->pile[0].count)
		goto GRAB_FROM_PILE;
	else
		return;
GRAB_FROM_CORPSE:
	ITEM_MOVE_MENU(local_area[e->coords].corpse->inventory,e->inventory);
GRAB_FROM_PILE:
	ITEM_MOVE_MENU(local_area[e->coords].pile,e->inventory);
}
void use_rand(entity_t *e)
{
	int opts[INV_SIZE],c=0;
	for (int i=0;e->inventory[i].count;i++)
		if (e->inventory[i].type->use)
			opts[c++]=i;
	if (!c)
		return;
	e->inventory[opts[rand()%c]].type->use(e);
}
void grab_rand(entity_t *e)
{
	int c=0;
	tile_t *t=&local_area[e->coords];
	islot_t *p;
	if (t->pile[0].count&&t->corpse&&t->corpse->inventory[0].count)
		p=rand()%2?t->pile:t->corpse->inventory;
	else if (t->corpse&&t->corpse->inventory[0].count)
		p=t->corpse->inventory;
	else if (t->pile[0].count)
		p=t->pile;
	else
		return;
	for (;p[c].count;c++);
	if (!c)
		return;
	c=rand()%c;
	add_item(e->inventory,p[c].type,p[c].count);
	remove_slot(p,c);
}
