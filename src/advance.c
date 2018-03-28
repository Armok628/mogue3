#include "advance.h"
void kill_entity(entity_t *entity)
{
	int c=entity->coord;
	entity->hp=0;
	if (local_area[c].corpse)
		free(local_area[c].corpse);
	local_area[c].corpse=entity;
	local_area[c].e=NULL;
}
void entity_collision(entity_t *e1,entity_t *e2)
{
	if (e1==e2)
		return;
	e2->hp-=e1->str; // Temporary
	if (e2->hp<=0)
		kill_entity(e2);
	announce("e s e s d s",e1,"strikes",e2,"for",e1->str,"damage");
}
void wall_collision(entity_t *e,tile_t *wall)
{ // Handles interactions with "walls"
	switch (wall->fg) {
	case '+': // Door
		if (wall->fg_c==BROWN)
			wall->fg='\0'; // Open door
		return;
	// TODO: More cases?
	}
}
void move_entity(entity_t *entity,int from,int to)
{
	local_area[to].e=entity;
	local_area[from].e=NULL;
	entity->coord=to;
	draw_posl(from);
	draw_posl(to);
}
void try_move(entity_t *entity,int from,int to)
{
	tile_t *dest=&local_area[to];
	if (to<0||to>=AREA) // Detect vertical wrap
		return;
	int h=xcmp(to)-xcmp(from);
	if (h>1||h<-1) // Detect horizontal wrap
		return;
	if (dest->fg&&(entity->props&SOLID)) { // Wall and solid entity
		wall_collision(entity,dest);
		return; // No opportunity to move
	}
	if (dest->e) // Entity
		entity_collision(entity,dest->e);
	if (!dest->e)
		move_entity(entity,from,to);
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
