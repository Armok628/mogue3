#ifndef MOVE_H
#define MOVE_H
#include "announce.h"
#include "area.h"
#include "entity.h"
#include "items.h"
#include "map.h"
#include "target.h"

int max_damage(entity_t *,entity_t *);
int damage(entity_t *,entity_t *);
void kill_entity(entity_t *);
bool legal_move(int,int);
void try_move(entity_t *,int,int);
#endif
