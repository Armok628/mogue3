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
		int l=lin(x,y+i);
		make_wall(&a[l]);
		l=lin(x+w-1,y+i);
		make_wall(&a[l]);
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
	int hw=0,vw=0,walls=0,floors=0,doors=0;
	for (int x=-1;x<=1;x++)
		for (int y=-1;y<=1;y++) {
			int c=i+lin(x,y);
			vw+=!x&&y&&area[c].fg=='%';
			hw+=!y&&x&&area[c].fg=='%';
			walls+=area[c].fg=='%';
			floors+=area[c].bg=='#';
			doors+=area[c].fg=='+';
		}
	// Inside room
	if (sym=='+') { // Door
		if ((hw==2&&!vw)||(!hw&&vw==2))
			return false;
		if (hw==1||vw==1)
			return true;
		if (doors>1||walls<2||walls>4)
			return true;
	} else if (sym=='%') { // Wall
		if (walls+floors+doors<9) // Border of room
			return false;
		if (walls>3)//&&!doors)
			return true;
		if (walls<2)
			return true;
	}
	return false;
}
void fix_gap(tile_t *area,int i)
{
	if (area[i].bg!='#')
		return;
	int hw=0,vw=0,walls=0,floors=0,doors=0;
	for (int x=-1;x<=1;x++)
		for (int y=-1;y<=1;y++) {
			int c=i+lin(x,y);
			vw+=area[c].fg=='%'&&!x&&y;
			hw+=area[c].fg=='%'&&!y&&x;
			walls+=area[c].fg=='%';
			floors+=area[c].bg=='#';
			doors+=area[c].fg=='+';
		}
	if (walls+floors+doors<9) { // Border of room
		if (!doors)
			make_door(&area[i]);
		else
			make_wall(&area[i]);
	} else { // Inside room
		if (!doors&&walls<5&&((hw==2&&!vw)||(!hw&&vw==2)))
			make_door(&area[i]);
		else if (hw==1&&vw==1)
			make_wall(&area[i]);
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
	for (int i=0;i<4;i++)
		for (int c=0;c<AREA;c++)
			fix_gap(area,c);
	while (cull_walls(area));
}
int dist_to_room(tile_t *area,int c,char dir)
{
	int o=input_offset(dir),d=1;
	while (legal_move(c,c+o)) {
		c+=o;
		char bg=area[c].bg;
		if (bg=='#'||bg=='%'||area[c].fg=='+')
			return d;
		d++;
	}
	return -1;
}
void floor_line(tile_t *area,int c,int l,char dir)
{
	if (l<0)
		return;
	make_floor(&area[c]);
	int o=input_offset(dir);
	for (int i=0;i<l;i++)
		make_floor(&area[c+=o]);
	make_door(&area[c]);
}
bool make_path(tile_t *area,int c)
{
	if (area[c].bg=='#')
		return false;
	announce("s d d","Trying for path at",xcmp(c),ycmp(c));
	int h=dist_to_room(area,c,'h');
	int j=dist_to_room(area,c,'j');
	int k=dist_to_room(area,c,'k');
	int l=dist_to_room(area,c,'l');
	announce("d d d d",h,j,k,l);
	/*
	if ((h>0)+(j>0)+(k>0)+(l>0)>=2)
		return false; // Not enough possible directions
	announce("s","Making paths");
	// Make actual paths
	if ((h>j)+(h>k)+(h>l)>=2)
		floor_line(area,c,h,'h');
	if ((j>h)+(j>k)+(j>l)>=2)
		floor_line(area,c,j,'j');
	if ((k>h)+(k>j)+(k>l)>=2)
		floor_line(area,c,k,'k');
	if ((l>h)+(l>j)+(l>k)>=2)
		floor_line(area,c,l,'l');
	*/
	if (h>0) floor_line(area,c,h,'h');
	if (j>0) floor_line(area,c,j,'j');
	if (k>0) floor_line(area,c,k,'k');
	if (l>0) floor_line(area,c,l,'l');
	return true;
}
void random_path(tile_t *area)
{ // Keep trying random coordinates until success
	while (!make_path(area,rand()%AREA));
}
