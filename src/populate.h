#ifndef POPULATE_H
#define POPULATE_H
#include "types.h"
#include "area.h"
#include "entity.h"
#include "spawn.h"

void populate(wtile_t *,tile_t *,bool);
void spawn_loot(wtile_t *,tile_t *);
#endif
