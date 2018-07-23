#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include "area.h"
#include "randword.h"
#include "spells.h"
#include "terminal.h"
#include "types.h"
extern etype_t player_etype;
extern etype_t human_etype;
extern etype_t monster_etype;
extern entity_t *player;

void draw_entity(entity_t *);
void redraw(entity_t *);
void transform(entity_t *,etype_t *);
entity_t *spawn(etype_t *);
void init_perm_effects(entity_t *e);
void spawn_at(tile_t *,etype_t *,int);
#endif
