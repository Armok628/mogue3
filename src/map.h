#ifndef MAP_H
#define MAP_H
#include "announce.h"
#include "area.h"
#include "entity.h"
#include "genarea.h"
#include "input.h"
#include "items.h"
#include "populate.h"
#include "quit.h"
#include "terminal.h"
#include "world.h"

extern int map_coords;

int rand_land_coords();
void enter_area(tile_t *);
void enter_map_cell(int);
void open_map();
#endif
