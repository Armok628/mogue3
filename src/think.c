#include "think.h"
char think(entity_t *e)
{
	if (!(rand()%10))
		return '5'; // Wait
	if ((rand()%100)<e->wis)
		return 'm'; // Cast spell
	int mov_opts[9],atk_opts[9];
	int n_atks=0,n_movs=0;
	int coords=e->coords;
	for (int dx=-1;dx<=1;dx++)
		for (int dy=-1;dy<=1;dy++) {
			if (!dx&&!dy)
				continue;
			int c=coords+lin(dx,dy);
			if (!legal_move(coords,c)) // Illegal move
				continue;
			char f=local_area[c].fg;
			if (f&&f!='+'&&e->flags&SOLID) // Non-door wall and solid self
				continue;
			entity_t *t=local_area[c].e;
			if (!t||!friend(e,t)||enemy(e,t)) // Absent, nonfriend, or enemy
				mov_opts[n_movs++]=c; // Possible move
			else if (t&&enemy(e,t)&&!friend(e,t)) // Present and nonfriend enemy
				atk_opts[n_atks++]=c; // Possible attack
		}
	int dest;
	if (n_atks)
		dest=atk_opts[rand()%n_atks];
	else if (n_movs)
		dest=mov_opts[rand()%n_movs];
	else
		dest=generate_input();
	return offset_input(dest-coords);
}
