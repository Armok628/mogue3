#include "room.h"
void make_door(int x,int y)
{
	int l=lin(x,y);
	local_area[l].fg='+';
	local_area[l].fg_c=BROWN;
	local_area[l].bg='-';
	local_area[l].bg_c=BROWN;
}
void make_room(int x,int y,int width,int height,dir_t direction)
{
	for (int xo=0;xo<width;xo++)
		for (int yo=0;yo<height;yo++) {
			int l=lin(x+xo,y+yo);
			local_area[l].fg='\0';
			local_area[l].bg='#';
			local_area[l].bg_c=LGRAY;
		}
	for (int i=0;i<width;i++) {
		int l1=lin(x+i,y),l2=lin(x+i,y+height-1);
		local_area[l1].fg='%';
		local_area[l1].fg_c=DGRAY;
		local_area[l2].fg='%';
		local_area[l2].fg_c=DGRAY;
	}
	for (int i=0;i<height;i++) {
		int l1=lin(x,y+i),l2=lin(x+width-1,y+i);
		local_area[l1].fg='%';
		local_area[l1].fg_c=DGRAY;
		local_area[l2].fg='%';
		local_area[l2].fg_c=DGRAY;
	}
	switch (direction) {
	case NORTH:
		make_door(x+width/2,y);
		break;
	case SOUTH:
		make_door(x+width/2,y+height);
		break;
	case EAST:
		make_door(x+width,y+height/2);
		break;
	case WEST:
		make_door(x,y+height/2);
	}
}
