#ifndef INVENTORY_H
#define INVENTORY_H
#include <stdlib.h>
#include "menu.h"
#include "types.h"
#define ITEM_MOVE_MENU(inv,pile) { \
	int s=item_menu(inv); \
	itype_t *t=inv[s].type; \
	if (s<0) \
		return;\
	int c=inv[s].count;\
	if (c>1)\
		c=int_prompt("How many? ");\
	if (!c)\
		return;\
	add_item(pile,t,remove_item(inv,t,c));\
	return; \
}

int item_menu(islot_t []);
int add_item(islot_t [],itype_t *,int);
int item_count(islot_t [],itype_t *);
void remove_slot(islot_t [],int);
int remove_item(islot_t [],itype_t *,int);
void use_menu(entity_t *);
bool equipped(entity_t *,itype_t *);
void drop_menu(entity_t *);
void equip_menu(entity_t *);
void unequip_menu(entity_t *);
void grab_menu(entity_t *);
void use_rand(entity_t *);
void grab_rand(entity_t *);
#endif
