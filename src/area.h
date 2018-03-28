#ifndef AREA_H
#define AREA_H
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
extern tile_t *local_area;

#define N_GRASS 6
extern const char grass[N_GRASS];

// X and Y components of linear index
static inline int xcmp(int l)
{
	return (l%WIDTH);
}
static inline int ycmp(int l)
{
	return (l/WIDTH);
}
static inline int lin(int x,int y)
{
	return (x+y*WIDTH);
}

void draw_pos(int,int);
void draw_posl(int);
void draw_local_area();
tile_t *new_area();
#endif
