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
void populate_with(tile_t *area,etype_t *type,int amt,bool dungeon)
{
	amt=enforce_range(amt,type->quota);
	if (amt<1)
		return;
	sflag_t sf=type->spawn_flags;
	void (*spawn_fp)(tile_t *,etype_t *)=&spawn_randomly;
	if (dungeon) { // Force inside
		spawn_fp=spawn_inside;
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
bool appropriate(wtile_t *tile,etype_t *type)
{ // Returns true if type should spawn in tile's area
	if (type->spawn_flags==NONE)
		return false;
	if (!tile) // NULL tile : temporary area (i.e. dungeon)
		return type->spawn_flags&DUNGEON;
	if (tile->town&&!(type->spawn_flags&TOWN)) {
		return false;
	}
	if (!tile->town&&!(type->spawn_flags&WILDERNESS)) {
		return false;
	}
	if (!in_range(tile->elevation,type->elev)) {
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
			int n=pops[i]+1;
			populate_with(area,spawnlist[i],n,!w);
		}
	}
	free(pops);
}
void spawn_items(wtile_t *w,tile_t *area,itype_t *type,int count)
{
	if (!count)
		return;
	int (*get_coord)(tile_t *)=&empty_coords;
	sflag_t sf=type->spawn_flags;
	if (!w&&sf&DUNGEON)
		get_coord=&inside_coords;
	else if ((sf&INSIDE)&&(sf&OUTSIDE))
		get_coord=&empty_coords;
	else if (sf&INSIDE)
		get_coord=&empty_coords;
	else if (sf&OUTSIDE)
		get_coord=&outside_coords;
	add_item(area[get_coord(area)].pile,type,count);
}
void spawn_loot(wtile_t *w,tile_t *area,ltab_t *table)
{
	for (int i=0;table->items[i];i++) {
		if (rand()%100>table->chances[i])
			continue;
		int c=ranged_rand(table->amounts[i]);
		int o=ranged_rand(table->occurrences[i]);
		for (int j=0;j<o;j++)
			spawn_items(w,area,table->items[i],c);
	}
}
