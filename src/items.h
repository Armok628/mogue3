#ifndef ITEMS_H
#define ITEMS_H
#include <stdlib.h>
#include "bool.h"
#include "types.h"

extern bool has_axe;
extern int logs;
extern int rocks;
extern bool has_raft;
extern bool has_canoe;
extern itype_t sword;
extern itype_t gold;

item_t *spawn_item(itype_t *);
#endif
