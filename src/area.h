#ifndef WORLD_H
#define WORLD_H
#include "terminal.h"
typedef struct entity_s entity_t;
#include "entity.h"

typedef struct tile_s {
	entity_t *e,*corpse;
	color_t fg_c,bg_c;
	char fg,bg;
} tile_t;

#define WIDTH 80
#define HEIGHT 24
#define AREA (HEIGHT*WIDTH)
extern tile_t area[AREA];

#define N_GRASS 6
extern const char grass[N_GRASS];

void putc_pos(char,int,int);
void draw_pos(int,int);
void draw_posl(int);
void draw_area();
#endif
