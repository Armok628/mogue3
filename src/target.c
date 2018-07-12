#include "target.h"
bool visible(int c1,int c2)
{
	float x1=xcmp(c1),x2=xcmp(c2);
	float y1=ycmp(c1),y2=ycmp(c2);
	float d_x=x2-x1,d_y=y2-y1;
	float mag=sqrt(d_x*d_x+d_y*d_y);
	float dx=d_x/mag,dy=d_y/mag;
	for (float d=0;d<mag;d+=1) {
		int x=round(x1+=dx);
		int y=round(y1+=dy);
		tile_t *t=&local_area[lin(x,y)];
		if (x==x2&&y==y2)
			return true;
		if (t->fg||t->e)
			return false;
		//set_color(WHITE,BG BLACK);
		//putc_pos('#',x,y);
	}
	return true;
}
int player_target()
{ // Does not enforce fog of war
	int c=player->coords;
	char input;
	clear_announcements();
	do {
		if (visible(player->coords,c))
			set_color(YELLOW,BG BLACK);
		else
			set_color(LRED,BG BLACK);
		putc_pos('X',xcmp(c),ycmp(c));
		if (local_area[c].e)
			announce_stats(local_area[c].e);
		input=fgetc(stdin);
		draw_posl(c);
		int d=c+input_offset(input);
		if (legal_move(c,d))
			c=d;
		clear_announcements();
	} while (input!='\n'&&input!='q');
	clear_announcements();
	announce_stats(player);
	return c;
}
bool friend(entity_t *c1,entity_t *c2)
{
	for (int i=0;c1->type->friends[i];i++)
		if (c1->type->friends[i]==c2->type)
			return true;
	return false;
}
bool enemy(entity_t *c1,entity_t *c2)
{
	for (int i=0;c1->type->enemies[i];i++)
		if (c1->type->enemies[i]==c2->type)
			return true;
	return false;
}
entity_t *target_by(entity_t *caster,cat_t c,bool corpse)
{ // Enforces fog of war
	int targets[100],n_targets=0,t;
	if (caster==player) {
		t=player_target();
		if (!visible(caster->coords,t))
			return NULL;
		goto RETURN_TARGET;
	}
	for (int i=0;i<AREA;i++) {
		if (!visible(caster->coords,i))
			continue;
		entity_t *t;
		if (corpse)
			t=local_area[i].corpse;
		else
			t=local_area[i].e;
		if (!t||t==caster)
			continue;
		if (c==OFFENSE?!friend(caster,t):friend(caster,t))
			targets[n_targets++]=t->coords;
	}
	if (!n_targets)
		return NULL;
	t=targets[rand()%n_targets];
RETURN_TARGET:
	if (corpse)
		return local_area[t].corpse;
	else
		return local_area[t].e;
}
entity_t *target_friend(entity_t *caster)
{
	return target_by(caster,DEFENSE,false);
}
entity_t *target_enemy(entity_t *caster)
{
	return target_by(caster,OFFENSE,false);
}
entity_t *target_corpse(entity_t *caster)
{
	return target_by(caster,DEFENSE,true);
}
