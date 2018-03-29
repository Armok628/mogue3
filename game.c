#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
int main(int argc,char **argv)
{
	srand(time(NULL));
	set_cursor_visible(0);
	set_canon(0);
	clear_screen();

	world=worldgen(3,0);
	map_coords=rand_land_coords();
	wtile_t *w=&world[map_coords];
	w->area=generate_area(w->symbol,w->color);
	local_area=w->area;
	player=place_randomly(&playertype);
	place_randomly(&monstertype);

	/**/
	make_room(10,10,5,5,NORTH);
	/**/

	draw_local_area();
	announce_stats(player);
	for (;;)
		advance();
}
