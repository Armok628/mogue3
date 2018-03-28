#include "advance.h"
void take_turn(entity_t *e)
{
	int old_coord=e->coord,new_coord=old_coord;
	char input;
	if (e==player) {
		input=fgetc(stdin);
		clear_announcements();
	} else
		input=generate_input();
	new_coord+=input_offset(input);
	try_move(e,old_coord,new_coord);
}
void advance()
{
	// Unchanging entity pointer array prevents multiple turns per step
	static entity_t *e[AREA];
	for (int i=0;i<AREA;i++)
		e[i]=local_area[i].e;
	for (int i=0;i<AREA;i++)
		if (e[i]&&e[i]->hp>0) // HP check to avoid post-death turns
			take_turn(e[i]);
}
