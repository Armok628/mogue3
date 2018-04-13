#include "debug.h"
static char *debug_options[]={
	"Swap bodies",
	"Make room",
	"Fix rooms",
	"Make path",
	"Random path",
	"Give canoe",
	"Kill entity",
	"Show inventory"
};
static int n_debug_options=sizeof(debug_options)/sizeof(char *);
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
		break;
	case 2: // Fix rooms
		fix_rooms(local_area);
		break;
	case 3: // Make path
		make_path(local_area,player->coords);
		break;
	case 4: // Random path
		random_path(local_area);
		break;
	case 5: // Give canoe
		has_canoe=true;
		break;
	case 6: // Kill entity
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		kill_entity(local_area[opt].e);
		break;
	case 7: // Show inventory
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		item_t **items=local_area[opt].e->inventory;
		for (int i=0;items[i];i++)
			announce("s sds",items[i]->type->name,"(",items[i]->count,")");
		break;
	}
	draw_local_area();
}
