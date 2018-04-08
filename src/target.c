#include "target.h"
int player_target()
{
	int c=player->coords;
	char input;
	clear_announcements();
	do {
		set_color(YELLOW,BG BLACK);
		putc_pos('X',xcmp(c),ycmp(c));
		if (local_area[c].e)
			announce_stats(local_area[c].e);
		input=fgetc(stdin);
		draw_posl(c);
		c+=input_offset(input);
		clear_announcements();
	} while (input!='\n'&&input!='q');
	clear_announcements();
	return c;
}
int target_by(entity_t *caster)
{
	if (caster==player)
		return player_target();
	return rand()%AREA; // Temporary
}
