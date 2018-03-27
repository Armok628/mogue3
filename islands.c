#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/terminal.h"
#define WIDTH 80
#define HEIGHT 24
#define AREA (WIDTH*HEIGHT)
int avg_pt(int l[WIDTH][HEIGHT],int x,int y)
{
	int sum=0;
	// Add up orthogonal heights (including self)
	for (int xo=-1;xo<=1;xo++)
		sum+=l[x+xo][y];
	for (int yo=-1;yo<=1;yo++)
		sum+=l[x][y+yo];
	// Add up heights in 3x3 grid (including self)
	for (int yo=-1;yo<=1;yo++)
		for (int xo=-1;xo<=1;xo++)
			sum+=l[x+xo][y+yo];
	return sum/15; // Take average
}
void erode(int land[WIDTH][HEIGHT])
{
	int tmp[WIDTH][HEIGHT];
	for (int y=0;y<HEIGHT;y++)
		for (int x=0;x<WIDTH;x++)
			tmp[x][y]=land[x][y];
	for (int y=1;y<HEIGHT-1;y++)
		for (int x=1;x<WIDTH-1;x++)
			land[x][y]=avg_pt(tmp,x,y);
}
color_t height_color(int height)
{
	if (height>65)
		return WHITE;
	if (height>60)
		return LGRAY;
	else if (height>53)
		return GREEN;
	else if (height>50)
		return LGREEN;
	else if (height>48)
		return YELLOW;
	else if (height>44)
		return LBLUE;
	else if (height>24)
		return BLUE;
	else
		return BLACK;
}
char height_symbol(int height)
{
	if (height>65)
		return '^';
	if (height>60)
		return '=';
	else if (height>55)
		return '-';
	else if (height>48)
		return '~';
	else
		return '_';
}
void draw_land(int land[WIDTH][HEIGHT])
{
	for (int y=0;y<HEIGHT;y++) {
		for (int x=0;x<WIDTH;x++) {
			int h=land[x][y];
			set_color(height_color(h),BG BLACK);
			putchar(height_symbol(h));
		}
		putchar('\n');
	}
}
void interactive_gen(int land[WIDTH][HEIGHT])
{
	char input='\0';
	clear_screen();
	move_cursor(0,HEIGHT);
	printf("Press e to erode. Press q to quit.\n");
	set_cursor_visible(0);
	set_canon(0);
	while (input!='q') {
		move_cursor(0,0);
		draw_land(land);
		input=fgetc(stdin);
		if (input=='e')
			erode(land);
	}
	set_canon(1);
	set_cursor_visible(1);
	set_color(RESET,BG RESET);
}
int main(int argc,char **argv)
{
	printf("\e[2J\e[0;0H");
	int world[WIDTH][HEIGHT];
	long seed;
	if (argc>1)
		sscanf(argv[1],"%ld",&seed);
	else
		seed=time(NULL);
	srand(seed);
	for (int y=0;y<HEIGHT;y++)
		for (int x=0;x<WIDTH;x++) {
			if (!x||!y||x==WIDTH-1||y==HEIGHT-1)
				world[x][y]=0;
			else // TODO: Base the following number on AREA
				world[x][y]=rand()%100;
		}
	interactive_gen(world);
	move_cursor(0,HEIGHT+1);
	printf("Seed: %ld\n",seed);
	return 0;
}
