#include "area.h"
tile_t *local_area;
const char grass[N_GRASS]={',','.','\'','"','`',';'};
void draw_tile(tile_t tile)
{
	if (tile.e)
		draw_entity(tile.e);
	else if (tile.corpse)
		draw_entity(tile.corpse);
	else if (tile.fg) {
		set_color(tile.fg_c,BG BLACK);
		putchar(tile.fg);
	} else {
		set_color(tile.bg_c,BG BLACK);
		putchar(tile.bg);
	}
}
void draw_pos(int x,int y)
{
	if (x<0||x>=WIDTH||y<0||y>=HEIGHT)
		return;
	move_cursor(x,y);
	draw_tile(local_area[lin(x,y)]);
}
void draw_posl(int c)
{
	if (c<0||c>=AREA)
		return;
	move_cursor(xcmp(c),ycmp(c));
	draw_tile(local_area[c]);
}
void draw_local_area()
{
	for (int i=0;i<AREA;i++)
		draw_posl(i);
}
int empty_coords(tile_t *area)
{
	int c=rand()%AREA;
	while (area[c].fg||area[c].e)
		c=rand()%AREA;
	return c;
}
