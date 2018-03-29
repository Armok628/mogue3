#include "map.h"
int map_coords;
void draw_star(int pos)
{
	set_color(RED,BG BLACK);
	putc_pos('*',xcmp(pos),ycmp(pos));
}
void map_move(int pos)
{
	if (world[pos].elevation>48) { // TODO: Other conditions
		draw_world_posl(map_coords);
		map_coords=pos;
	}
}
void close_map()
{
	wtile_t *w=&world[map_coords];
	if (!w->area)
		w->area=new_area();
	local_area=w->area;
	int lpos=rand()%AREA;
	while (local_area[lpos].e||local_area[lpos].fg)
		lpos=rand()%AREA;
	local_area[lpos].e=player;
	player->coords=lpos;
	draw_local_area();
	announce_stats(player);
}
int rand_land_coords()
{
	int c=rand()%W_AREA;
	while (world[c].elevation<=48)
		c=rand()%W_AREA;
	return c;
}
void open_map()
{
	if (!world) {
		world=worldgen(3,0);
		map_coords=rand_land_coords();
		world[map_coords].area=local_area;
	}
	local_area[player->coords].e=NULL;
	clear_announcements();
	clear_screen();
	draw_world();
	for (;;) {
		draw_star(map_coords);
		char input=fgetc(stdin);
		if (input=='w')
			break;
		map_move(map_coords+input_offset(input));
	}
	close_map();
}
