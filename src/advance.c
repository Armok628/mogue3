#include "advance.h"
static bool map_opened=false;
void handle_input(entity_t *e,char input)
{
	int o=input_offset(input);
	if (o) {
		try_move(e,e->coords,e->coords+o);
		return;
	}
	switch (input) {
	case '\0': // ^@
		debug_menu();
		//handle_input(player,fgetc(stdin));
		return;
	case 'R':
		clear_screen();
		clear_announcements();
		draw_local_area();
		announce_stats(player);
		handle_input(player,fgetc(stdin));
		return;
	case 'a':
		action_menu();
		return;
	case 'c':
		o=input_offset(fgetc(stdin));
		if (local_area[e->coords+o].bg=='-') {
			local_area[e->coords+o].fg='+';
			draw_posl(e->coords+o);
		}
		return;
	case 'm': // TODO: Generalize across all entities
		spell_menu(e);// Temporary
		return;
	case 'w':
		if (local_area[e->coords].bg!='#') {
			open_map();
			map_opened=true;
		} else
			announce("s","You must be outside to travel");
		return;
	case '?':
		target_by(player);
		return;
	case 'i':
		select_item(e->inventory);
		return;
	case 'd':
		drop_menu(e);
		return;
	case 'g':
		grab_menu(e);
		return;
	case 'e':
		equip_menu(e);
		return;
	case 'r':
		unequip_menu(e);
		return;
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
	handle_input(e,key);
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
