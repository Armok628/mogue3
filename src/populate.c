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
int (*loc_finder(wtile_t *w,sflag_t sf,range_t elev))(tile_t *)
{ // Returns function for getting spawn location, null if inappropriate
	if (sf==NONE)
		return NULL;
	if (!w)
		return sf&DUNGEON?&empty_coords:NULL;
	else if ((!in_range(w->elevation,elev))
			||(w->town&&!(sf&TOWN))
			||(!w->town&&!(sf&WILDERNESS)))
		return NULL;
	if ((sf&INSIDE)&&(sf&OUTSIDE))
		return &empty_coords;
	else if (sf&INSIDE)
		return &inside_coords;
	else if (sf&OUTSIDE)
		return &outside_coords;
	return NULL;
}
void populate(wtile_t *w,tile_t *area,bool persist)
{
	int n_creatures=2*entityspawn_size+rand()%(persist?(AREA/96):(AREA/192));
	int pops[entityspawn_size];
	rand_fixed_sum(entityspawn_size,n_creatures,pops);
	for (int i=0;i<entityspawn_size;i++) {
		etype_t *e=entityspawn[i];
		if (w&&(!persist^!(e->flags&PERSISTS)))
			continue;
		if (rand()%100>=e->freq.chance)
			continue;
		int (*spawn_loc)(tile_t *)=loc_finder(w,e->spawn_flags,e->elev);
		if (!spawn_loc)
			continue;
		int n=enforce_range(pops[i]+1,e->freq.counts);
		for (int i=0;i<n;i++)
			spawn_at(area,e,spawn_loc(area));
	}
}
void spawn_loot(wtile_t *w,tile_t *area)
{
	for (int i=0;i<itemspawn_size;i++) {
		itype_t *t=itemspawn[i];
		if (rand()%100>=t->freq.chance)
			continue;
		int (*spawn_loc)(tile_t *)=loc_finder(w,t->spawn_flags,t->elev);
		if (!spawn_loc)
			continue;
		int p=ranged_rand(t->freq.times);
		for (int j=0;j<p;j++) {
			int c=spawn_loc(area);
			int amt=ranged_rand(t->freq.counts);
			add_item(area[c].pile,t,amt);
		}
	}
}
