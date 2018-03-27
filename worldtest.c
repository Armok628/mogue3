#include "src/world.h"
int main(int argc,char **argv)
{
	int world[W_WIDTH][W_HEIGHT];
	long seed=time(NULL);
	int offset=0,erosion=3;
	if (argc>1)
		for (int i=1;i<argc;i++) {
			sscanf(argv[i],"seed=%ld",&seed);
			sscanf(argv[i],"offset=%d",&offset);
			sscanf(argv[i],"erosion=%d",&erosion);
		}
	srand(seed);
	// Generate world
	for (int y=0;y<W_HEIGHT;y++)
		for (int x=0;x<W_WIDTH;x++) {
			if (!x||!y||x==W_WIDTH-1||y==W_HEIGHT-1)
				world[x][y]=0;
			else // TODO: Base the following number on AREA
				world[x][y]=rand()%100;
		}
	for (int i=0;i<erosion;i++)
		erode(world);
	if (offset)
		elevate(world,offset);
	// Display
	clear_screen();
	move_cursor(0,0);
	printf("Seed: %ld\n",seed);
	draw_land(world);
	set_color(RESET,BG RESET);
	putchar('\n');
	return 0;
}
