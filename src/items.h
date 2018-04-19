#ifndef ITEMS_H
#define ITEMS_H
#include <stdlib.h>
#include "menu.h"
#include "types.h"

extern int logs;
extern int rocks;
extern bool has_raft;
extern bool has_canoe;
extern itype_t sword;
extern itype_t gold;
extern itype_t axe;

item_t *spawn_item(itype_t *);
int select_item(item_t *[]);
void add_item(item_t *[],item_t *);
item_t *remove_item(item_t *[],int);
void remove_type(item_t *[],itype_t *);
void drop_item(entity_t *,int);
void drop_menu(entity_t *);
void loot_item(entity_t *,int);
void grab_item(entity_t *,int);
void grab_menu(entity_t *);
void equip(entity_t *,int);
void equip_menu(entity_t *);
void unequip(entity_t *,int);
void unequip_menu(entity_t *);
bool equipped(entity_t *,itype_t *);
#endif
