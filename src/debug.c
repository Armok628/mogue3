#include "debug.h"
static char *debug_options[]={
	"Swap bodies",
	"Make room",
	"Fix rooms",
	"Make path",
	"Random path",
	"Give canoe",
	"Kill entity",
	"Show inventory",
	"Inventory menu",
	"Check visibility"
};
static int n_debug_options=sizeof(debug_options)/sizeof(char *);
void draw_visible()
{
	for (int i=0;i<AREA;i++)
		if (visible(player->coords,i))
			draw_posl(i);
}
void debug_menu()
{
	int opt=menu(debug_options,n_debug_options);
	switch (opt) {
	case 0: // Swap bodies
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		player=local_area[opt].e;
		break;
	case 1: // Make room
		random_room(local_area);
		world[map_coords].city=true;
		draw_local_area();
		break;
	case 2: // Fix rooms
		fix_rooms(local_area);
		draw_local_area();
		break;
	case 3: // Make path
		make_path(local_area,player->coords);
		draw_local_area();
		break;
	case 4: // Random path
		random_path(local_area);
		draw_local_area();
		break;
	case 5: // Give canoe
		has_canoe=true;
		break;
	case 6: // Kill entity
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		kill_entity(local_area[opt].e);
		draw_posl(opt);
		break;
	case 7: // Show inventory
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		islot_t *items=local_area[opt].e->inventory;
		for (int i=0;items[i].count;i++)
			announce("s sds",items[i].type->name,"(",items[i].count,")");
		break;
	case 8: // Inventory menu
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		select_item(local_area[opt].e->inventory);
		break;
	case 9: // Check visibility
		clear_screen();
		draw_visible();
	}
}
