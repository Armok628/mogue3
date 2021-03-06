#include "debug.h"
void draw_visible(int c)
{
	clear_screen();
	for (int i=0;i<AREA;i++)
		if (visible(c,i))
			draw_posl(i);
}
extern bool on_canoe;
void debug_command()
{
	char *input=string_prompt("Command: ");
	char stat[4];
	int num;
	if (!strcmp(input,"swap")) {
		entity_t *t=local_area[player_target()].e;
		if (!t)
			announce("s","No target");
		else
			player=t;
	} else if (!strcmp(input,"kill")) {
		entity_t *t=local_area[player_target()].e;
		if (!t)
			announce("s","No target");
		else {
			announce("e s",t,"mysteriously dies");
			kill_entity(t);
			draw_posl(t->coords);
		}
	} else if (!strcmp(input,"resurrect")) {
		int c=player_target();
		tile_t *t=&local_area[c];
		if (!t||!t->corpse||t->e) {
			announce("s","No target");
		} else {
			t->e=t->corpse;
			t->corpse=NULL;
			t->e->hp=t->e->maxhp;
			announce("e s",t->e,"mysteriously comes back to life");
			draw_posl(c);
		}
	} else if (!strcmp(input,"canoe")) {
		on_canoe=true;
	} else if (!strcmp(input,"teleport")) {
		int c=player_target();
		if (local_area[c].e)
			free_entity(local_area[c].e);
		move_entity(player,player->coords,c);
	} else if (!strcmp(input,"fog_of_war")) {
		fog_of_war=!fog_of_war;
		draw_local_area();
	} else if (!strcmp(input,"inventory")) {
		int c=player_target();
		entity_t *e=local_area[c].e;
		if (!e)
			return;
		item_menu(e->inventory);
	} else if (!strcmp(input,"dragon")) {
		int c=player_target();
		spawn_at(local_area,&dragon_etype,c);
	} else if (sscanf(input,"set %3[^=]=%d",stat,&num)==2) {
		entity_t *t=local_area[player_target()].e;
		if (!t)
			announce("s","No target");
		else if (!strcmp(stat,"res"))
			t->res=num;
		else if (!strcmp(stat,"agi"))
			t->agi=num;
		else if (!strcmp(stat,"wis"))
			t->wis=num;
		else if (!strcmp(stat,"str"))
			t->str=num;
		else if (!strcmp(stat,"hp")) {
			t->hp=num;
			if (t->hp>t->maxhp)
				t->maxhp=t->hp;
		} else
			announce("s","Invalid stat");
	} else
		announce("s","Unrecognized command");
	free(input);
}
