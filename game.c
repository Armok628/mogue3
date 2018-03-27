#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
int main(int argc,char **argv)
{
	srand(time(NULL));
	for (int i=0;i<AREA;i++) {
		area[i].bg=grass[rand()%N_GRASS];
		area[i].bg_c=rand()%2?GREEN:LGREEN;
	}
	set_cursor_visible(0);
	set_canon(0);
	clear_screen();

	player=place_randomly(&playertype);
	place_randomly(&monstertype);

	draw_area();
	announce_stats(player);

	/*
	int choice=menu(argv,argc);
	announce("ss","You picked ",argv[choice]);
	*/

	/*
	entity_t e,*c=&e;
	c->symbol='M';
	c->color=PURPLE;
	c->hp=1;
	c->wis=10;
	c->spells[0]=&heal_self;

	announce("sdc","c->health=",c->hp);
	//c->spells[0](c);
	cast(c,0);
	announce("sdc","c->health=",c->hp);

	//clear_announcements();
	*/
	for (;;)
		advance();

}
