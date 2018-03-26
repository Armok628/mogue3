#include "advance.h"
void resolve_collision(entity_t *e1,entity_t *e2)
{
	e2->hp-=e1->str; // Temporary
	if (e2->hp<=0)
		e2->hp=0;
}
void move_entity(entity_t *entity,int from,int to)
{ // To-do: Detect illegal movements
	if (area[to].fg)
		return;
	if (area[to].e)
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
int handle_input(char input)
{
	int digit=input-'0';
	if (0<digit&&digit<10) {
		digit--;
		return (digit%3-1)+WIDTH*(1-digit/3);
	} else
		switch (input) {
		case 'h':
			return -1;
		case 'l':
			return 1;
		case 'j':
			return WIDTH;
		case 'k':
			return -WIDTH;
		case 'q':
			quit();
		default:
			return 0;
		}
}
int generate_input()
{
	return handle_input(1+rand()%9+'0');
}
void take_turn(entity_t *e)
{
	int old_coord=e->coord,new_coord=e->coord;
	if (e==player)
		new_coord+=handle_input(fgetc(stdin));
	else
		new_coord+=generate_input();
	move_entity(e,old_coord,new_coord);
}
void advance()
{
	for (int i=0;i<AREA;i++)
		if (area[i].e)
			take_turn(area[i].e);
	clear_announcements();
}
