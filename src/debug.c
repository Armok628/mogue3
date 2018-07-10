#include "debug.h"
static char *debug_options[]={
	"Swap bodies",
	"Make room",
	"Fix rooms",
	"Random path",
	"Give canoe",
	"Kill entity",
	"Resurrect entity",
	"Check visibility",
	"Think",
	"Set health",
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
	char s[2]=" ";
	tile_t *t;
	switch (opt) {
	case 0: // Swap bodies
		opt=player_target();
		if (!local_area[opt].e)
			return;
		player=local_area[opt].e;
		break;
	case 1: // Make room
		random_room(local_area);
		world[map_coords].town=true;
		draw_local_area();
		break;
	case 2: // Fix rooms
		fix_rooms(local_area);
		draw_local_area();
		break;
	case 3: // Random path
		random_path(local_area);
		draw_local_area();
		break;
	case 4: // Give canoe
		has_canoe=true;
		break;
	case 5: // Kill entity
		opt=player_target();
		if (!local_area[opt].e)
			return;
		kill_entity(local_area[opt].e);
		draw_posl(opt);
		break;
	case 6: // Resurrect entity
		opt=player_target();
		t=&local_area[opt];
		if (!t->corpse||t->e)
			return;
		t->e=t->corpse;
		t->corpse=NULL;
		t->e->hp=t->e->maxhp;
		draw_posl(opt);
		break;
	case 7: // Check visibility
		clear_screen();
		draw_visible();
		break;
	case 8: // Think
		s[0]=think(player);
		announce("s s","Think:",s);
		break;
	case 9: // Set health
		player->hp=int_prompt("Set health to:");
		break;
	}
}
