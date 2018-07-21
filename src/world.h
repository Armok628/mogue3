#ifndef WORLD_H
#define WORLD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "area.h"
#include "input.h"
#include "terminal.h"
#include "types.h"

extern wtile_t *world;

wtile_t *worldgen(int,int);
void draw_world_tile(wtile_t *);
void draw_world_pos(int,int);
void draw_world_posl(int);
void draw_world();
#endif
