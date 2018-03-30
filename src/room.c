#include "room.h"
void make_door(tile_t *t)
{
	t->fg='+';
	t->fg_c=BROWN;
	t->bg='-';
	t->bg_c=BROWN;
}
void make_floor(tile_t *t)
{
	t->fg='\0';
	t->bg='#';
	t->bg_c=LGRAY;
}
void make_wall(tile_t *t)
{
	t->fg='%';
	t->fg_c=DGRAY;
	t->bg='%';
	t->bg_c=DGRAY;
}
void make_room(tile_t *a,int x,int y,int w,int h,dir_t direction)
{
	for (int xo=0;xo<w;xo++)
		for (int yo=0;yo<h;yo++)
			make_floor(&a[lin(x+xo,y+yo)]);
	for (int i=0;i<w;i++) {
		make_wall(&a[lin(x+i,y)]);
		make_wall(&a[lin(x+i,y+h-1)]);
	}
	for (int i=0;i<h;i++) {
		int l1=lin(x,y+i),l2=lin(x+w-1,y+i);
		make_wall(&a[l1]);
		make_wall(&a[l2]);
	}
	switch (direction) {
	case NORTH:
		make_door(&a[lin(x+w/2,y)]);
		break;
	case SOUTH:
		make_door(&a[lin(x+w/2,y+h-1)]);
		break;
	case EAST:
		make_door(&a[lin(x+w-1,y+h/2)]);
		break;
	case WEST:
		make_door(&a[lin(x,y+h/2)]);
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
	char sym=area[i].fg;
	if (area[i].fg!='%'&&area[i].fg!='+')
		return false;
	int orthw=0,walls=0,floors=0,doors=0;
	for (int x=-1;x<=1;x++)
		for (int y=-1;y<=1;y++) {
			int c=i+lin(x,y);
			orthw+=!x^!y&&area[c].bg=='%';
			walls+=area[c].bg=='%';
			floors+=area[c].bg=='#';
			doors+=area[c].bg=='-';
		}
	if (walls+floors+doors<9) // Border of room
		return false;
	// Inside room
	if (sym=='+') { // Door
		if (doors>1||walls>3)
			return true;
	} else if (sym=='%') { // Wall
		if (walls>3&&!doors)
			return true;
		if (walls<2)
			return true;
	}
	return false;
}
void fix_gap(tile_t *area,int i)
{
	char sym=area[i].fg;
	if (area[i].bg!='#')
		return;
	int orthw=0,walls=0,floors=0,doors=0;
	for (int x=-1;x<=1;x++)
		for (int y=-1;y<=1;y++) {
			int c=i+lin(x,y);
			orthw+=!x^!y&&area[c].bg=='%';
			walls+=area[c].bg=='%';
			floors+=area[c].bg=='#';
			doors+=area[c].bg=='-';
		}
	if (walls+floors+doors<9) { // Border of room
		if (!doors)
			make_door(&area[i]);
		else
			make_wall(&area[i]);
	} else { // Inside room
		if (orthw==2&&walls<5&&!doors)
			make_door(&area[i]);
	}
}
int cull_walls(tile_t *area)
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
void fix_rooms(tile_t *area)
{
	while (cull_walls(area));
	for (int i=0;i<AREA;i++)
		fix_gap(area,i);
	while (cull_walls(area));
}
