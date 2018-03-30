#include "map.h"
int map_coords;
void draw_star(int pos)
{
	set_color(playertype.color,BG BLACK);
	putc_pos('*',xcmp(pos),ycmp(pos));
}
void map_move(int pos)
{
	if (has_raft||world[pos].elevation>48) { // TODO: Other conditions
		draw_world_posl(map_coords);
		map_coords=pos;
	}
}
void close_map()
{
	wtile_t *w=&world[map_coords];
	if (!w->area)
		w->area=generate_area(w->symbol,w->color);
	local_area=w->area;
	int lpos=empty_coords(local_area);
	local_area[lpos].e=player;
	player->coords=lpos;
	draw_local_area();
	announce_stats(player);
}
int rand_land_coords()
{
	int c=rand()%AREA;
	while (world[c].elevation<=48)
		c=rand()%AREA;
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
		clear_announcements();
		draw_star(map_coords);
		char input=fgetc(stdin);
		if (input=='w')
			break;
		else if (input=='q') {
			free(player);
			quit();
		}
		map_move(map_coords+input_offset(input));
	}
	close_map();
}
