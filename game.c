#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
int main(int argc,char **argv)
{
	long seed=time(NULL);
	int erosion=3,offset=0;
	if (argc>1)
		for (int i=1;i<argc;i++) {
			sscanf(argv[i],"seed=%ld",&seed);
			sscanf(argv[i],"offset=%d",&offset);
			sscanf(argv[i],"erosion=%d",&erosion);
		}
	fprintf(stderr,"%ld",seed);
	srand(seed);
	set_cursor_visible(0);
	set_canon(0);
	clear_screen();

	world=worldgen(erosion,offset);
	map_coords=rand_land_coords();
	wtile_t *w=&world[map_coords];
	w->area=generate_area(w);
	local_area=w->area;

	player=place_randomly(&playertype);
	place_randomly(&monstertype);

	draw_local_area();
	announce_stats(player);
	for (;;)
		advance();
}
