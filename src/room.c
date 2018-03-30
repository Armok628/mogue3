#include "room.h"
void make_door(tile_t *a,int x,int y)
{
	int l=lin(x,y);
	a[l].fg='+';
	a[l].fg_c=BROWN;
	a[l].bg='-';
	a[l].bg_c=BROWN;
}
void make_room(tile_t *a,int x,int y,int w,int h,dir_t direction)
{
	for (int xo=0;xo<w;xo++)
		for (int yo=0;yo<h;yo++) {
			int l=lin(x+xo,y+yo);
			a[l].fg='\0';
			a[l].bg='#';
			a[l].bg_c=LGRAY;
		}
	for (int i=0;i<w;i++) {
		int l1=lin(x+i,y),l2=lin(x+i,y+h-1);
		a[l1].fg='%';
		a[l1].fg_c=DGRAY;
		a[l1].bg='%';
		a[l1].bg_c=DGRAY;
		a[l2].fg='%';
		a[l2].fg_c=DGRAY;
		a[l2].bg='%';
		a[l2].bg_c=DGRAY;
	}
	for (int i=0;i<h;i++) {
		int l1=lin(x,y+i),l2=lin(x+w-1,y+i);
		a[l1].fg='%';
		a[l1].fg_c=DGRAY;
		a[l1].bg='%';
		a[l1].bg_c=DGRAY;
		a[l2].fg='%';
		a[l2].fg_c=DGRAY;
		a[l2].bg='%';
		a[l2].bg_c=DGRAY;
	}
	switch (direction) {
	case NORTH:
		make_door(a,x+w/2,y);
		break;
	case SOUTH:
		make_door(a,x+w/2,y+h-1);
		break;
	case EAST:
		make_door(a,x+w-1,y+h/2);
		break;
	case WEST:
		make_door(a,x,y+h/2);
	}
}
void random_room(tile_t *a)
{
	int w=3+rand()%(WIDTH/4);
	int h=3+rand()%(HEIGHT/4);
	int x=1+rand()%(WIDTH-w-2);
	int y=1+rand()%(HEIGHT-h-2);
	if (x+w>WIDTH)
		x-=w;
	if (y+h>HEIGHT)
		y-=h;
	make_room(a,x,y,w,h,(dir_t)rand()%4);
}
bool wall_needs_cull(tile_t *area,int i)
{
	if (area[i].fg=='%') {
		if (area[i+1].fg=='+'&&!area[i+2].fg)
			return true;
		if (area[i-1].fg=='+'&&!area[i-2].fg)
			return true;
		if (area[i+WIDTH].fg=='+'&&!area[i+2*WIDTH].fg)
			return true;
		if (area[i-WIDTH].fg=='+'&&!area[i-2*WIDTH].fg)
			return true;
	}
	if (area[i].fg=='%'||area[i].fg=='+') {
		if (area[i+1].bg=='#'&&area[i-1].bg=='#')
			return true;
		if (area[i+WIDTH].bg=='#'&&area[i-WIDTH].bg=='#')
			return true;
	}
	return false;
}
int cull_iteration(tile_t *area)
{
	int walls_removed=0;
	for (int i=WIDTH+1;i<AREA-WIDTH-1;i++)
		if (wall_needs_cull(area,i)) {
			area[i].fg='\0';
			area[i].bg='#';
			area[i].bg_c=LGRAY;
			walls_removed++;
		}
	return walls_removed;
}
void cull_walls(tile_t *area)
{
	// Call cull_iteration until it does nothing
	while (cull_iteration(area));
}
