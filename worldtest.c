#include "src/world.h"
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
	srand(seed);
	world=worldgen(erosion,offset);
	clear_screen();
	draw_world();
	move_cursor(0,W_HEIGHT);
	set_color(RESET,BG RESET);
	printf("Seed: %ld\n",seed);
	putchar('\n');
	return 0;
}
