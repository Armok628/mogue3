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
		return;
	} else if (sf&INSIDE)
		spawn_fp=&spawn_inside;
	else if (sf&OUTSIDE)
		spawn_fp=&spawn_outside;
	for (int i=0;i<amt;i++)
		spawn_fp(area,type);
}
bool appropriate(wtile_t *tile,sflag_t sf,range_t elev)
{ // Returns true if type should spawn in tile's area
	if (sf==NONE)
		return false;
	if (!tile) // NULL tile : temporary area (i.e. dungeon)
		return sf&DUNGEON;
	if (tile->town&&!(sf&TOWN)) {
		return false;
	}
	if (!tile->town&&!(sf&WILDERNESS)) {
		return false;
	}
	if (!in_range(tile->elevation,elev)) {
		return false;
	}
	return true;
}
void populate(wtile_t *w,tile_t *area,bool persist)
{
	int n_creatures=2*entityspawn_size+rand()%(persist?(AREA/96):(AREA/192));
	int pops[entityspawn_size];
	rand_fixed_sum(entityspawn_size,n_creatures,pops);
	for (int i=0;i<entityspawn_size;i++) {
		if (w&&(!persist^!(entityspawn[i]->flags&PERSISTS)))
			continue;
		if (appropriate(w,entityspawn[i]->spawn_flags,entityspawn[i]->elev))
			populate_with(area,entityspawn[i],pops[i]+1,!w);
	}
}
void spawn_pile(wtile_t *w,tile_t *area,itype_t *type,int count)
{ // TODO: Abstract mutual task(s) between spawn_pile and populate_with
	if (!count)
		return;
	int (*get_coord)(tile_t *)=&empty_coords;
	sflag_t sf=type->spawn_flags;
	if (!w&&sf&DUNGEON)
		get_coord=&inside_coords;
	else if (!w)
		return;
	else if ((sf&INSIDE)&&(sf&OUTSIDE))
		get_coord=&empty_coords;
	else if (sf&INSIDE)
		get_coord=&inside_coords;
	else if (sf&OUTSIDE)
		get_coord=&outside_coords;
	add_item(area[get_coord(area)].pile,type,count);
}
void spawn_loot(wtile_t *w,tile_t *area)
{
	for (int i=0;i<itemspawn_size;i++) {
		itype_t *t=itemspawn[i];
		if (rand()%100>=t->freq.chance)
			continue;
		if (!appropriate(w,t->spawn_flags,t->elev))
			continue;
		int p=ranged_rand(t->freq.times);
		for (int j=0;j<p;j++) {
			int c=ranged_rand(t->freq.counts);
			spawn_pile(w,area,t,c);
		}
	}
}
