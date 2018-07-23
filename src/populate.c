#include "populate.h"
void rand_fixed_sum(int n,int max,int ret[])
{ // Fills ret as an array of n random elements whose sum is max
	int arr[n+1];
	for (int i=0;i<n-1;i++)
		arr[i]=rand()%max;
	arr[n-1]=0;
	arr[n]=max;
	// Bubblesort
	bool sorted=false;
	do {
		sorted=true;
		for (int i=1;i<n+1;i++)
			if (arr[i]<arr[i-1]) {
				sorted=false;
				int tmp=arr[i];
				arr[i]=arr[i-1];
				arr[i-1]=tmp;
			}
	} while (!sorted);
	// Difference transform
	for (int i=0;i<n;i++)
		ret[i]=arr[i+1]-arr[i];
}
void populate_with(tile_t *area,etype_t *type,int amt,bool dungeon)
{
	if (rand()%100>=type->freq.chance)
		return;
	amt=enforce_range(amt,type->freq.counts);
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
	int pops[spawnlist_size];
	rand_fixed_sum(spawnlist_size,n_creatures,pops);
	for (int i=0;i<spawnlist_size;i++) {
		if (w&&(!persist^!(spawnlist[i]->flags&PERSISTS)))
			continue;
		if (appropriate(w,spawnlist[i]))
			populate_with(area,spawnlist[i],pops[i]+1,!w);
	}
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
void spawn_loot(wtile_t *w,tile_t *area,ltab_t *lt)
{ // TODO: Make dynamic with loot table of all items
	for (int i=0;(*lt)[i].type;i++) {
		if (rand()%100>(*lt)[i].freq.chance)
			continue;
		int o=ranged_rand((*lt)[i].freq.times);
		for (int j=0;j<o;j++) {
			int c=ranged_rand((*lt)[i].freq.counts);
			spawn_items(w,area,(*lt)[i].type,c);
		}
	}
}
