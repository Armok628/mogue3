#include "advance.h"
void resolve_collision(entity_t *e1,entity_t *e2)
{
	if (e1==e2)
		return;
	e2->hp-=e1->str; // Temporary
	if (e2->hp<=0)
		e2->hp=0;
	announce("e s e s d s",e1,"strikes",e2,"for",e1->str,"damage");
}
void move_entity(entity_t *entity,int from,int to)
{
	if (to<0||to>=AREA) // Detect vertical wrap
		return;
	int h=(to%WIDTH)-(from%WIDTH);
	if (h>1||h<-1) // Detect horizontal wrap
		return;
	if (area[to].fg) // Wall
		return;
	if (area[to].e) // Entity
		resolve_collision(entity,area[to].e);
	if (!area[to].e||area[to].e->hp==0) {
		if (area[to].corpse)
			free(area[to].corpse);
		area[to].corpse=area[to].e;
		area[to].e=entity;
		entity->coord=to;
		area[from].e=NULL;
	}
	draw_posl(from);
	draw_posl(to);
}
int input_offset(char input)
{
	int digit=input-'0';
	if (0<digit&&digit<10) {
		// Numpad input handling
		digit--;
		return (digit%3-1)+WIDTH*(1-digit/3);
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
	move_entity(e,old_coord,new_coord);
}
void advance()
{
	// Unchanging entity pointer array prevents multiple turns per step
	entity_t *e[AREA];
	for (int i=0;i<AREA;i++)
		e[i]=area[i].e;
	for (int i=0;i<AREA;i++)
		if (e[i]&&e[i]->hp>0) // HP check to avoid post-death turns
			take_turn(e[i]);
}
