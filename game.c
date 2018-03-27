#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
int main(int argc,char **argv)
{
	srand(time(NULL));
	set_cursor_visible(0);
	set_canon(0);
	clear_screen();
	local_area=new_area();

	player=place_randomly(&playertype);
	place_randomly(&monstertype);
	draw_local_area();
	announce_stats(player);

	for (;;)
		advance();
}
