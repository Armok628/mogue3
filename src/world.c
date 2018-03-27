#include "world.h"
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
	else if (elevation>55)
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
