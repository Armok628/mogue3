#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 40
#define HEIGHT 20
int avg_pt(int l[WIDTH][HEIGHT],int x,int y)
{
	int sum=0;
	for (int x=-1;x<=1;x++)
		for (int y=-1;y<=1;y++)
			sum+=l[x][y];
	return sum/5;
}
void erode(int land[WIDTH][HEIGHT])
{
	int tmp[WIDTH][HEIGHT];
	for (int x=1;x<WIDTH-1;x++)
		for (int y=1;y<HEIGHT-1;y++)
			tmp[x][y]=land[x][y];
	for (int x=1;x<WIDTH-1;x++)
		for (int y=1;y<HEIGHT-1;y++)
			land[x][y]=avg_pt(tmp,x,y);
}
void print_land(int land[WIDTH][HEIGHT])
{
	for (int x=0;x<WIDTH;x++) {
		for (int y=0;y<HEIGHT;y++)
			printf("(%3d)",land[x][y]);
		putchar('\n');
	}
}
int main(int argc,char **argv)
{
	int world[WIDTH][HEIGHT];
	srand(time(NULL));
	for (int x=0;x<WIDTH;x++)
		for (int y=0;y<HEIGHT;y++) {
			if (!x||!y)
				world[x][y]=0;
			else
				world[x][y]=rand()%(rand()%200?5:100);
		}
	print_land(world);
	erode(world);
	print_land(world);
}
