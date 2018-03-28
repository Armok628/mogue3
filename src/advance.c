#include "advance.h"
int input_offset(char input)
{
	int digit=input-'0';
	if (0<digit&&digit<10) {
		// Numpad input handling
		digit--;
		return lin(digit%3-1,1-digit/3);
	} else
		switch (input) {
		case 'h':
			return -1;
		case 'j':
			return WIDTH;
		case 'k':
			return -WIDTH;
		case 'l':
			return 1;
		case 'y':
			return -1-WIDTH;
		case 'u':
			return 1-WIDTH;
		case 'b':
			return -1+WIDTH;
		case 'n':
			return 1+WIDTH;
		case 'q':
			quit();
		default:
			return 0;
		}
}
int generate_input()
{
	return rand()%10+'0';
}
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
