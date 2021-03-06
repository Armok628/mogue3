#ifndef QUIT_H
#define QUIT_H
#include "announce.h"
#include "area.h"
#include "advance.h"
#include "entity.h"
#include "world.h"

void free_entity(entity_t *);
void free_area(tile_t *);
void quit();
void player_death();
#endif
