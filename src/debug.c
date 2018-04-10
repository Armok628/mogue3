#include "debug.h"
static char *debug_options[]={
	"Make room",
	"Fix rooms",
	"Make path",
	"Random path",
	"Give canoe",
	"Kill entity"
};
static int n_debug_options=sizeof(debug_options)/sizeof(char *);
void debug_menu()
{
	int opt=menu(debug_options,n_debug_options);
	switch (opt) {
	case 0: // Make room
		random_room(local_area);
		world[map_coords].city=true;
		break;
	case 1: // Fix rooms
		fix_rooms(local_area);
		break;
	case 2: // Make path
		make_path(local_area,player->coords);
		break;
	case 3: // Random path
		random_path(local_area);
		break;
	case 4: // Give canoe
		has_canoe=true;
		break;
	case 5: // Kill entity
		opt=target_by(player);
		if (!local_area[opt].e)
			return;
		kill_entity(local_area[opt].e);
	}
	draw_local_area();
}
