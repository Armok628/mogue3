#include "map.h"
bool on_canoe=false;
int map_coords;
void draw_star(int pos)
{
	set_color(player_etype.color,BG BLACK);
	putc_pos('*',xcmp(pos),ycmp(pos));
}
void map_move(int pos)
{
	int elevation=world[pos].elevation;
	if (elevation<25) // World border
		return;
	bool landing=world[map_coords].landing;
	if (!(landing||on_canoe)&&elevation<45) // Deep sea
		return;
	if (!(equipped(player,&raft)||on_canoe||landing)&&elevation<49) // Shallow water
		return;
	int l1=world[map_coords].elevation>48;
	int l2=elevation>48;
	if (l1^l2) { // Land <=> Sea
		if (l2&&equipped(player,&raft)) {
			announce("s","The raft breaks in the landing");
			remove_item(player->equipped,&raft,1);
		} else if (l2) {
			announce("s","You land your canoe");
			world[pos].landing=true;
			on_canoe=false;
		} else if (l1&&equipped(player,&raft)) {
			announce("s","You embark on your raft");
		} else if (l1&&(on_canoe||landing)) {
			announce("s","You embark on your canoe");
			on_canoe=true;
			world[map_coords].landing=false;
		}
	}
	draw_world_posl(map_coords);
	map_coords=pos;
}
void enter_area(tile_t *area)
{
	local_area=area;
	int lpos=empty_coords(local_area);
	local_area[lpos].e=player;
	player->coords=lpos;
	draw_local_area();
}
void enter_map_cell(int coords)
{
	wtile_t *w=&world[coords];
	if (!w->area)
		w->area=generate_area(w);
//	for (int i=0;i<10;i++) spawn_outside(w->area,&monster_etype);
	populate(w,w->area,false);
	map_coords=coords;
	enter_area(w->area);
	next_line();
}
int rand_land_coords()
{
	int c=rand()%AREA;
	while (world[c].elevation<=48)
		c=rand()%AREA;
	return c;
}
void remove_temps(tile_t *area)
{
	for (int i=0;i<AREA;i++) {
		entity_t *e=area[i].e,*c=area[i].corpse;
		if (e&&~e->flags&PERSISTS) {
			free_entity(e);
			area[i].e=NULL;
		}
		if (c&&~c->flags&PERSISTS) {
			free_entity(c);
			area[i].corpse=NULL;
		}
	}
}
void open_map()
{
	remove_temps(local_area);
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
		char input=get_input();
		clear_announcements();
		if (input=='w')
			break;
		else if (input=='q') {
			free_entity(player); // because not in any area
			next_line();
			quit();
		}
		map_move(map_coords+input_offset(input));
	}
	clear_announcements();
	enter_map_cell(map_coords);
}
