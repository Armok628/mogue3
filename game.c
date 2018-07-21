#include <signal.h>
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
void flush_exit(int sig)
{
	if (sig==SIGINT) {
		announce("s","Keyboard interrupt.\n");
		quit();
	}
	if (sig==SIGSEGV)
		announce("s","Segmentation fault.");
	fflush(record);
	announce("s","Recording flushed.");
	set_canon(true);
	set_cursor_visible(true);
	next_line();
	exit(sig);
}
int main(int argc,char **argv)
{
	signal(SIGSEGV,&flush_exit);
	signal(SIGINT,&flush_exit);
	long seed=time(NULL);
	int erosion=3,offset=0;
	char filename[50];
	if (argc>1)
		for (int i=1;i<argc;i++) {
			sscanf(argv[i],"seed=%ld",&seed);
			sscanf(argv[i],"offset=%d",&offset);
			sscanf(argv[i],"erosion=%d",&erosion);
			if (sscanf(argv[i],"record=%50s",filename)) {
				if (record)
					fclose(record);
				record=fopen(filename,"w");
			}
			if (sscanf(argv[i],"replay=%50s",filename)) {
				if (replay)
					fclose(replay);
				replay=fopen(filename,"r");
			}

		}
	if (!record)
		record=fopen("/tmp/mogue3replay","w");
	if (replay)
		fscanf(replay,"seed=%ld;offset=%d;erosion=%d\n",&seed,&offset,&erosion);
	else
		replay=stdin;
	fprintf(record?record:stderr,"seed=%ld;offset=%d;erosion=%d\n",seed,offset,erosion);
	srand(seed);
	set_cursor_visible(false);
	set_canon(false);
	clear_screen();
	world=worldgen(erosion,offset);
	player=spawn(&player_etype);
	enter_map_cell(rand_land_coords());
	for (;;) {
		take_turn(player);
		advance();
	}
}
