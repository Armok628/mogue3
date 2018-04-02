#ifndef ROOM_H
#define ROOM_H
#include "announce.h" // Temporary
#include "area.h"
#include "bool.h"
#include "input.h"
#include "move.h"

typedef enum {NORTH,SOUTH,EAST,WEST} dir_t;

void make_room(tile_t *,int,int,int,int,dir_t);
void random_room(tile_t *);
void fix_rooms(tile_t *);
bool make_path(tile_t *,int);
void random_path(tile_t *);
#endif
