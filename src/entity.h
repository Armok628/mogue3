#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include "area.h"
#include "spells.h"
#include "terminal.h"
#include "types.h"
extern etype_t player_etype;
extern etype_t human_etype;
extern etype_t monster_etype;
extern entity_t *player;

void draw_entity(entity_t *);
void redraw(entity_t *);
entity_t *spawn(etype_t *);
entity_t *spawn_randomly(tile_t *area,etype_t *);
entity_t *spawn_inside(tile_t *area,etype_t *);
entity_t *spawn_outside(tile_t *area,etype_t *);
#endif
