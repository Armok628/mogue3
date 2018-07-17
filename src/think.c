#include "think.h"
bool would_flee(entity_t *flee_r,entity_t *flee_e)
{
	int d=flee_r->wis>10?max_damage(flee_e,flee_r):damage(flee_e,flee_r);
	return d>flee_r->hp||flee_r->res*2<flee_e->str+flee_e->agi;
}
char cw(char dir)
{
	static const char *cws="00142132475563788996";
	if ('0'<=dir&&dir<='9')
		return cws[2*(dir-'0')+1];
	return '0';
}
char ccw(char dir)
{
	static const char *ccws="00122336415569748798";
	if ('0'<=dir&&dir<='9')
		return ccws[2*(dir-'0')+1];
	return '0';
}
char alt_dir(int pos,char dir)
{ // Return alternate direction if path is blocked
	int dest=pos+input_offset(dir);
	tile_t *t=&local_area[dest];
	if (legal_move(pos,dest)&&!t->e&&!t->fg)
		return dir;
	bool occupied[2]={false,false};
	char dirs[2];
	dirs[0]=cw(dir);
	dirs[1]=ccw(dir);
	for (int i=0;i<4;i++) { // 4 rotations -> opposite direction
		for (int j=0;j<2;j++) {
			// Look both directions
			dest=pos+input_offset(dirs[j]);
			t=&local_area[dest];
			occupied[j]=!legal_move(pos,dest)||t->e||t->fg;
		}
		if (occupied[0]&&occupied[1]) { // Both blocked
			// Look further from path
			dirs[0]=cw(dirs[0]);
			dirs[1]=ccw(dirs[1]);
			continue;
		}
		if (occupied[0]^occupied[1]) // One blocked
			return occupied[0]?dirs[1]:dirs[0]; // Return other
		else // Neither blocked
			return dirs[rand()%2]; // Return random
	}
	return dirs[0];
}
char think(entity_t *e)
{
	if (!(rand()%10))
		return '5'; // Wait
	if (e->flags&CASTS_SPELLS&&(rand()%100)<e->wis)
		return 'm'; // Cast spell
	if (e->flags&USES_ITEMS) {
		if (e->inventory[0].count&&!(rand()%5))
			return 'i'; // Use item
		tile_t *t=&local_area[e->coords];
		if (t->pile[0].count||(t->corpse&&t->corpse->inventory[0].count))
			return 'g'; // Grab item
	}
	int mov_opts[9],atk_opts[9],flee_opts[9];
	int n_atk=0,n_mov=0,n_flee=0;
	int coords=e->coords;
	for (int dx=-1;dx<=1;dx++)
		for (int dy=-1;dy<=1;dy++) {
			if (!dx&&!dy)
				continue;
			int c=coords+lin(dx,dy);
			// Check for illegal move
			if (!legal_move(coords,c))
				continue;
			char f=local_area[c].fg;
			// Check for non-door wall and solid self
			if (f&&f!='+'&&e->flags&SOLID)
				continue;
			entity_t *t=local_area[c].e;
			// Check for absent, nonfriend, or enemy target
			if (!t||!friend(e,t)||enemy(e,t))
				mov_opts[n_mov++]=c; // Possible move
			// Check for present, nonfriend, and enemy target
			if (t&&enemy(e,t)&&!friend(e,t))
				atk_opts[n_atk++]=c; // Possible attack
			// Check for entity being nonfriend or enemy to target and would flee
			if (t&&(enemy(t,e)||!friend(t,e))&&would_flee(e,t))
				flee_opts[n_flee++]=c; // Possible flight
		}
	int dest=coords;
	if (n_flee) {
		dest=flee_opts[rand()%n_flee];
		announce("e s e",e,"flees from",local_area[dest].e);
		dest=coords-(dest-coords); // Reverse offset to dest -> reverse direction
		tile_t *t=&local_area[dest];
		return alt_dir(coords,offset_input(dest-coords));
	} else if (n_atk)
		dest=atk_opts[rand()%n_atk];
	else if (n_mov)
		dest=mov_opts[rand()%n_mov];
	return offset_input(dest-coords);
}
