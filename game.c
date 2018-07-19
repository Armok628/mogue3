#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "src/area.h"
#include "src/advance.h"
#include "src/entity.h"
#include "src/map.h"
#include "src/types.h"
#include "src/terminal.h"
#include "src/world.h"
int main(int argc,char **argv)
{
	long seed=time(NULL);
	int erosion=3,offset=0;
	char filename[50];
	if (argc>1)
		for (int i=1;i<argc;i++) {
			sscanf(argv[i],"seed=%ld",&seed);
			sscanf(argv[i],"offset=%d",&offset);
			sscanf(argv[i],"erosion=%d",&erosion);
			if (sscanf(argv[i],"record=%50s",filename))
				record=fopen(filename,"w");
			if (sscanf(argv[i],"replay=%50s",filename))
				replay=fopen(filename,"r");

		}
	if (replay)
		fscanf(replay,"seed=%ld\n",&seed);
	fprintf(record?record:stderr,"seed=%ld\n",seed);
	srand(seed);
	set_cursor_visible(0);
	set_canon(0);
	clear_screen();

	world=worldgen(erosion,offset);
	player=spawn(&player_etype);
	enter_map_cell(rand_land_coords());

	for (;;) {
		take_turn(player);
		advance();
	}
}
