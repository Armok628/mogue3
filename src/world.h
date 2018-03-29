#ifndef WORLD_H
#define WORLD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "terminal.h"
#include "area.h"

typedef struct wtile_s {
	tile_t *area;
	int elevation;
	char symbol;
	color_t color;
} wtile_t;

extern wtile_t *world;

wtile_t *worldgen(int,int);
void draw_world_tile(wtile_t *);
void draw_world_pos(int,int);
void draw_world_posl(int);
void draw_world();
#endif
