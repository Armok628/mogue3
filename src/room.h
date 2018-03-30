#ifndef ROOM_H
#define ROOM_H
#include "area.h"

typedef enum {NORTH,SOUTH,EAST,WEST} dir_t;

void make_room(int,int,int,int,dir_t);
void random_room();
#endif
