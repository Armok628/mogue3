#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/terminal.h"
#define WIDTH 80
#define HEIGHT 24
int avg_pt(int l[WIDTH][HEIGHT],int x,int y)
{
	int sum=0;
	for (int yo=-1;yo<=1;yo++)
		for (int xo=-1;xo<=1;xo++)
			sum+=l[x+xo][y+yo];
	return sum/9;
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
	if (height>500)
		return WHITE;
	else if (height>300)
		return DGRAY;
	else if (height>200)
		return LGRAY;
	else if (height>75)
		return GREEN;
	else if (height>50)
		return LGREEN;
	else if (height>47)
		return YELLOW;
	else if (height>40)
		return LBLUE;
	else
		return BLUE;
}
char height_symbol(int height)
{
	if (height>500)
		return '^';
	else if (height>200)
		return '=';
	else if (height>50)
		return '-';
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
int main(int argc,char **argv)
{
	printf("\e[2J\e[0;0H");
	int world[WIDTH][HEIGHT];
	srand(time(NULL));
	for (int y=0;y<HEIGHT;y++)
		for (int x=0;x<WIDTH;x++) {
			if (!x||!y||x==WIDTH-1||y==HEIGHT-1)
				world[x][y]=0;
			else
				world[x][y]=rand()%(rand()%200?100:10000);
		}
	draw_land(world);
	putchar('\n');
	erode(world);
	erode(world);
	erode(world);
	draw_land(world);
	set_color(RESET,BG RESET);
}
