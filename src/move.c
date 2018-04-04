#include "move.h"
void kill_entity(entity_t *entity)
{
	int c=entity->coords;
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
	int damage=rand()%e1->str;
	e2->hp-=damage; // Temporary
	if (e2->hp<=0)
		kill_entity(e2);
	announce("e s e s d s",e1,"strikes",e2,"for",damage,"damage");
}
void wall_collision(entity_t *e,tile_t *wall)
{ // Handles interactions with "walls"
	switch (wall->fg) {
	case '+': // Door
		if (wall->fg_c==BROWN)
			wall->fg='\0'; // Open door
		return;
	case 'P': // Axe
		if (e==player)
			has_axe=true;
		wall->fg='\0';
		return;
	case '|': // Tree
		if (has_axe)
			wall->fg='=';
		return;
	case '=':
		trees_chopped++;
		wall->fg='\0';
		return;
	}
}
void move_entity(entity_t *entity,int from,int to)
{
	local_area[to].e=entity;
	local_area[from].e=NULL;
	entity->coords=to;
	draw_posl(from);
	draw_posl(to);
}
bool legal_move(int from,int to)
{
	if (to<0||to>=AREA) // Detect vertical wrap
		return false;
	int h=xcmp(to)-xcmp(from);
	if (h>1||h<-1) // Detect horizontal wrap
		return false;
	return true;
}
void try_move(entity_t *entity,int from,int to)
{
	tile_t *dest=&local_area[to];
	if (!legal_move(from,to))
		return;
	if (dest->fg&&entity->flags&SOLID) { // Wall and solid entity
		wall_collision(entity,dest);
		draw_posl(from);
		draw_posl(to);
		return; // No opportunity to move
	}
	if (dest->e) // Entity
		entity_collision(entity,dest->e);
	// Entity may be gone after collision
	if (!dest->e&&!(dest->fg&&entity->flags&SOLID))
		move_entity(entity,from,to);
}
