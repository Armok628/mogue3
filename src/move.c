#include "move.h"
void kill_entity(entity_t *entity)
{
	int c=entity->coords;
	entity->hp=0;
	if (local_area[c].corpse)
		free_entity(local_area[c].corpse);
	local_area[c].corpse=entity;
	local_area[c].e=NULL;
	if (entity==player)
		player_death();
}
int category_effect(entity_t *e,cat_t c)
{
	islot_t *inv=e->inventory;
	int sum=0;
	for (int i=0;inv[i].count;i++)
		if (inv[i].type->category==c)
			sum+=inv[i].type->effect*inv[i].count;
	return sum;
}
int max_damage(entity_t *e1,entity_t *e2)
{
	int d=5*e1->str-e2->str/2;
	d+=category_effect(e1,OFFENSE);
	d-=category_effect(e2,DEFENSE);
	return d<0?0:d;
}
int damage(entity_t *e1,entity_t *e2)
{
	if (rand()%40>=20+e1->agi-e2->agi)
		return -1; // Sentinel value: -1 => dodge
	int m=max_damage(e1,e2);
	return m?rand()%m:0;
}
void entity_collision(entity_t *e1,entity_t *e2)
{
	if (e1==e2)
		return;
	int d=damage(e1,e2);
	if (d<0) {
		announce("e s e s",e1,"tries to strike",e2,"but was dodged");
		return;
	} else if (!d) {
		announce("e s e s",e1,"tries to strike",e2,"but misses");
		return;
	} else {
		announce("e s e s d s",e1,"strikes",e2,"for",d,"damage");
	}
	if (d>e2->hp/5) {
		printf(" and cripples it");
		e2->agi-=e2->agi>0;
	}
	e2->hp-=d;
	if (e2->hp<=0) {
		printf(", killing it!");
		kill_entity(e2);
	} else if (e2->hp>e2->maxhp/2&&!(rand()%5)) {
		announce("e s",e2,"is now tougher from it");
		e2->maxhp+=1+rand()%10;
	}
	if (!(rand()%5)&&e1->str<20) {
		announce("e s",e1,"is now stronger from it");
		e1->str++;
	}
}
void floor_collision(entity_t *e,tile_t *floor)
{
	int n;
	switch (floor->bg) {
		case '^':
			n=rand()%10;
			e->hp-=n;
			announce("e s d s",e,"stepped on a spike for",n,"damage");
			if (e->hp<=0) {
				printf(", killing it");
				kill_entity(e);
				draw_posl(e->coords);
			}
			break;
	}
}
void wall_collision(entity_t *e,tile_t *wall)
{ // Handles interactions with "walls"
	switch (wall->fg) {
	case '+': // Door
		if (e->flags&USES_ITEMS&&wall->fg_c==BROWN)
			wall->fg='\0'; // Open door
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
	if (entity->agi<=0) {
		announce("e s",entity,"is fully crippled ");
		// Maybe regain agility if totally crippled
		if (!(rand()%(20-entity->str))) {
			printf("but manages to stand back up");
			entity->agi++;
		} else
			printf("and fails to move");
		return;
	}
	if (~entity->flags&MOBILE) // Immobile
		return;
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
	if (!dest->e&&!(dest->fg&&entity->flags&SOLID)) {
		move_entity(entity,from,to);
		floor_collision(entity,dest);
		if (!(rand()%150)&&entity->agi<20) {
			announce("e s",entity,"is now more agile from moving");
			entity->agi++;
		}
	}
}
