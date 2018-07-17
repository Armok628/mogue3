#ifndef AREA_H
#define AREA_H
#include "entity.h"
#include "terminal.h"
#include "types.h"
#define WIDTH 80
#define HEIGHT 24
#define AREA (HEIGHT*WIDTH)
extern tile_t *local_area;
extern bool fog_of_war;

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
int empty_coords(tile_t *);
int inside_coords(tile_t *);
int outside_coords(tile_t *);
#endif
