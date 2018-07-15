#ifndef POPULATE_H
#define POPULATE_H
#include "types.h"
#include "area.h"
#include "entity.h"
#include "spawnlist.h"

void populate(wtile_t *,tile_t *,bool);
void spawn_loot(wtile_t *,tile_t *,ltab_t *);
#endif
