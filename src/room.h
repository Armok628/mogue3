#ifndef ROOM_H
#define ROOM_H
#include "area.h"
#include "bool.h"

typedef enum {NORTH,SOUTH,EAST,WEST} dir_t;

void make_room(tile_t *,int,int,int,int,dir_t);
void random_room(tile_t *);
void cull_walls(tile_t *);
#endif
