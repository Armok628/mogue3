#include "world.h"
wtile_t *world;
int avg_elev(int l[W_WIDTH][W_HEIGHT],int x,int y)
{
	int sum=0;
	// Add up orthogonal elevations (including self)
	for (int xo=-1;xo<=1;xo++)
		sum+=l[x+xo][y];
	for (int yo=-1;yo<=1;yo++)
		sum+=l[x][y+yo];
	// Add up elevations in 3x3 grid (including self)
	for (int yo=-1;yo<=1;yo++)
		for (int xo=-1;xo<=1;xo++)
			sum+=l[x+xo][y+yo];
	return sum/15; // Take average
}
void erode(int land[W_WIDTH][W_HEIGHT])
{
	int tmp[W_WIDTH][W_HEIGHT];
	for (int y=0;y<W_HEIGHT;y++)
		for (int x=0;x<W_WIDTH;x++)
			tmp[x][y]=land[x][y];
	for (int y=1;y<W_HEIGHT-1;y++)
		for (int x=1;x<W_WIDTH-1;x++)
			land[x][y]=avg_elev(tmp,x,y);
}
color_t elevation_color(int elevation)
{
	if (elevation>65)
		return WHITE;
	if (elevation>63)
		return DGRAY;
	if (elevation>60)
		return LGRAY;
	else if (elevation>53)
		return GREEN;
	else if (elevation>50)
		return LGREEN;
	else if (elevation>48)
		return YELLOW;
	else if (elevation>44)
		return LBLUE;
	else if (elevation>24)
		return BLUE;
	else
		return BLACK;
}
char elevation_symbol(int elevation)
{
	if (elevation>65)
		return '^';
	if (elevation>60)
		return '=';
	else if (elevation>56)
		return '-';
	else if (elevation>48)
		return '~';
	else
		return '_';
}
void draw_land(int land[W_WIDTH][W_HEIGHT])
{
	for (int y=0;y<W_HEIGHT;y++) {
		for (int x=0;x<W_WIDTH;x++) {
			int h=land[x][y];
			set_color(elevation_color(h),BG BLACK);
			putchar(elevation_symbol(h));
		}
		putchar('\n');
	}
}
void elevate(int land[W_WIDTH][W_HEIGHT],int offset)
{
	for (int x=0;x<W_WIDTH;x++)
		for (int y=0;y<W_HEIGHT;y++)
			land[x][y]+=offset;
}
wtile_t *worldgen(int erosion,int offset) // Default should be erosion=3, offset=0
{
	// Generate height map
	int elevs[W_WIDTH][W_HEIGHT];
	for (int y=0;y<W_HEIGHT;y++)
		for (int x=0;x<W_WIDTH;x++) {
			if (!x||!y||x==W_WIDTH-1||y==W_HEIGHT-1)
				elevs[x][y]=0;
			else // TODO: Base the following number on W_AREA
				elevs[x][y]=rand()%100;
		}
	for (int i=0;i<erosion;i++)
		erode(elevs);
	if (offset)
		elevate(elevs,offset);
	// Convert to wtiles
	wtile_t *w=malloc(W_AREA*sizeof(wtile_t));
	for (int i=0;i<W_AREA;i++) {
		int e=elevs[xcmp(i)][ycmp(i)];
		w[i].elevation=e;
		w[i].symbol=elevation_symbol(e);
		w[i].color=elevation_color(e);
		w[i].area=NULL;
	}
	return w;
}
void draw_world_tile(wtile_t *tile)
{
	set_color(tile->color,BG BLACK);
	putchar(tile->symbol);
}
void draw_world()
{
	for (int i=0;i<W_AREA;i++) {
		move_cursor(xcmp(i),ycmp(i));
		draw_world_tile(&world[i]);
	}
}
