#include "advance.h"
static bool map_opened=false;
void handle_key(entity_t *e,char key)
{
	int o=input_offset(key);
	if (o) {
		try_move(e,e->coords,e->coords+o);
		return;
	}
	switch (key) {
	case 'm':
		// TODO: Spellcasting
		break;
	case 'w':
		if (local_area[e->coords].bg!='#') {
			open_map();
			map_opened=true;
		} else {
			announce("s","You must be outside to travel");
		}
		break;
	case 'c':
		o=input_offset(fgetc(stdin));
		if (local_area[e->coords+o].bg=='-') {
			local_area[e->coords+o].fg='+';
			draw_posl(e->coords+o);
		}
		break;
	case 'q':
		quit();
	}
}
void take_turn(entity_t *e)
{
	int old_coords=e->coords,new_coords=old_coords;
	char key;
	if (e==player) {
		key=fgetc(stdin);
		clear_announcements();
		announce_stats(player);
	} else
		key=generate_input();
	handle_key(e,key);
}
void advance()
{
	// Unchanging entity pointer array prevents multiple turns per step
	static entity_t *e[AREA];
	for (int i=0;i<AREA;i++)
		e[i]=local_area[i].e;
	for (int i=0;i<AREA;i++) {
		if (!e[i]||!e[i]->hp)
			continue; // HP check to avoid post-death turns
		else
			take_turn(e[i]);
		if (map_opened) {
			map_opened=false;
			return;
		}
	}
}
