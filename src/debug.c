#include "debug.h"
static char *debug_options[]={
	"Make room",
	"Fix rooms",
	"Make path"
};
static int n_debug_options=sizeof(debug_options)/sizeof(char *);
void debug_menu()
{
	int opt=menu(debug_options,n_debug_options);
	switch (opt) {
	case 0: // Make room
		random_room(local_area);
		break;
	case 1: // Fix rooms
		fix_rooms(local_area);
		break;
	case 2: // Make path
		make_path(local_area,player->coords);
		break;
	}
	draw_local_area();
}
