#include "area.h"
tile_t *local_area;
bool fog_of_war=false;
void draw_tile(tile_t tile)
{
	if (tile.e)
		draw_entity(tile.e);
	else if (tile.corpse)
		draw_entity(tile.corpse);
	else if (tile.pile[0].count) {
		set_color(FG tile.pile[0].type->color BG BLACK);
		putchar(tile.pile[0].type->symbol);
	} else if (tile.fg) {
		set_color(FG tile.fg_c BG BLACK);
		putchar(tile.fg);
	} else {
		set_color(FG tile.bg_c BG BLACK);
		putchar(tile.bg);
	}
}
void draw_pos(int x,int y)
{
	if (replay!=stdin)
		return;
	if (x<0||x>=WIDTH||y<0||y>=HEIGHT)
		return;
	move_cursor(x,y);
	if (fog_of_war&&!visible(player->coords,lin(x,y))) {
		set_color(FG BLACK BG BLACK);
		putchar(' ');
	} else
		draw_tile(local_area[lin(x,y)]);
}
void draw_posl(int c)
{
	if (replay!=stdin)
		return;
	if (c<0||c>=AREA)
		return;
	move_cursor(xcmp(c),ycmp(c));
	if (fog_of_war&&!visible(player->coords,c)) {
		set_color(FG BLACK BG BLACK);
		putchar(' ');
	} else
		draw_tile(local_area[c]);
}
void draw_local_area()
{
	if (replay!=stdin)
		return;
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
int inside_coords(tile_t *area)
{
	int c=empty_coords(area);
	while (area[c].bg!='#')
		c=empty_coords(area);
	return c;
}
int outside_coords(tile_t *area)
{
	int c=empty_coords(area);
	while (area[c].bg=='#')
		c=empty_coords(area);
	return c;
}
