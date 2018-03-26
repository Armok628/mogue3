#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIDTH 40
#define HEIGHT 20
int avg_pt(int l[WIDTH][HEIGHT],int xc,int yc)
{
	int sum=0;
	sum+=l[xc+1][yc+1];
	sum+=l[xc+1][yc];
	sum+=l[xc+1][yc-1];
	sum+=l[xc][yc+1];
	sum+=l[xc][yc];
	sum+=l[xc][yc-1];
	sum+=l[xc-1][yc+1];
	sum+=l[xc-1][yc];
	sum+=l[xc-1][yc-1];
	return sum/9;
}
void erode(int land[WIDTH][HEIGHT])
{
	int tmp[WIDTH][HEIGHT];
	for (int x=0;x<WIDTH;x++)
		for (int y=0;y<HEIGHT;y++)
			tmp[x][y]=land[x][y];
	for (int x=1;x<WIDTH-1;x++)
		for (int y=1;y<HEIGHT-1;y++)
			land[x][y]=avg_pt(tmp,x,y);
}
char height_symbol(int height)
{
}
void print_land(int land[WIDTH][HEIGHT])
{
	for (int x=0;x<WIDTH;x++) {
		for (int y=0;y<HEIGHT;y++)
			printf("%4d ",land[x][y]);
		putchar('\n');
	}
}
int main(int argc,char **argv)
{
	printf("\e[2J\e[0;0H");
	int world[WIDTH][HEIGHT];
	srand(time(NULL));
	for (int x=0;x<WIDTH;x++)
		for (int y=0;y<HEIGHT;y++) {
			if (!x||!y||x==WIDTH-1||y==HEIGHT-1)
				world[x][y]=0;
			else
				world[x][y]=rand()%(rand()%200?100:10000);
		}
	print_land(world);
	putchar('\n');
	erode(world);
	erode(world);
	erode(world);
	print_land(world);
}
