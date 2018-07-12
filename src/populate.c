#include "populate.h"
int *rand_fixed_sum(int n,int max)
{ // Copied from mogue2
	int *arr=malloc(sizeof(int)*(n+1));
	for (int i=0;i<n-1;i++)
		arr[i]=rand()%max;
	arr[n-1]=0;
	arr[n]=max;
	// Bubblesort
	int sorted=0;
	do {
		sorted=1;
		for (int i=1;i<n+1;i++)
			if (arr[i]<arr[i-1]) {
				sorted=0;
				int tmp=arr[i];
				arr[i]=arr[i-1];
				arr[i-1]=tmp;
			}
	} while (!sorted);
	// Difference transform
	int *tmp=arr;
	int *new_arr=malloc(sizeof(int)*n);
	for (int i=0;i<n;i++)
		new_arr[i]=arr[i+1]-arr[i];
	arr=new_arr;
	free(tmp);
	return arr; // Returns array of n random elements whose sum is max
}
void populate_with(tile_t *area,etype_t *type,int amt)
{
	int min=type->min_sp,max=type->max_sp;
	amt=max>amt?min>amt?min:amt:max;
	if (!amt)
		return;
	sflag_t sf=type->spawn_flags;
	void (*spawn_fp)(tile_t *,etype_t *)=&spawn_randomly;
	if (amt<0) { // Force inside (as in a dungeon)
		spawn_fp=spawn_inside;
		amt=-amt;
	} else if ((sf&INSIDE)&&(sf&OUTSIDE)) {
		for (int i=0;i<amt/2;i++) {
			spawn_inside(area,type);
			spawn_outside(area,type);
		}
	} else if (sf&INSIDE)
		spawn_fp=&spawn_inside;
	else if (sf&OUTSIDE)
		spawn_fp=&spawn_outside;
	for (int i=0;i<amt;i++)
		spawn_fp(area,type);
}
#define IN_RANGE(min,val,max) (min<=val&&val<=max)
bool appropriate(wtile_t *tile,etype_t *type)
{ // Returns true if type should spawn in tile's area
	/*
	next_line();
	set_color(RESET,BG RESET);
	printf("Checking if %s is appropriate for ",type->name);
	draw_world_tile(tile);
	set_color(RESET,BG RESET);
	printf("... ");
	*/
	if (type->spawn_flags==NONE)
		return false;
	if (!tile) // NULL tile : temporary area (i.e. dungeon)
		return type->spawn_flags&DUNGEON;
	if (tile->town&&!(type->spawn_flags&TOWN)) {
		//printf("It isn't. (Town)");
		return false;
	}
	if (!tile->town&&!(type->spawn_flags&WILDERNESS)) {
		//printf("It isn't. (Wilderness)");
		return false;
	}
	if (!IN_RANGE(type->min_elev,tile->elevation,type->max_elev)) {
		//printf("It isn't. (Elevation requirements) ");
		//printf("%d<%d<%d",type->min_elev,tile->elevation,type->max_elev);
		return false;
	}
	return true;
}
void populate(wtile_t *w,tile_t *area,bool persist)
{
	int n_creatures=2*spawnlist_size+rand()%(persist?(AREA/96):(AREA/192));
	int *pops=rand_fixed_sum(spawnlist_size,n_creatures);
	for (int i=0;i<spawnlist_size;i++) {
		if (w&&(!persist^!(spawnlist[i]->flags&PERSISTS)))
			continue;
		if (appropriate(w,spawnlist[i])) {
			//announce("s s","Trying to spawn",spawnlist[i]->name);
			int n=pops[i]+1;
			if (!w)
				n=-n;
			populate_with(area,spawnlist[i],n);
		}
	}
	free(pops);
}
