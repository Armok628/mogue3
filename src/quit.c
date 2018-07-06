#include "quit.h"
void free_area(tile_t *a)
{
	for (int i=0;i<AREA;i++) {
		if (a[i].e)
			free(a[i].e);
		a[i].e=NULL;
		if (a[i].corpse)
			free(a[i].corpse);
		a[i].corpse=NULL;
	}
	free(a);
}
void free_world(wtile_t *w)
{
	for (int i=0;i<AREA;i++)
		if (w[i].area) {
			free_area(w[i].area);
			w[i].area=NULL;
		}
	free(w);
}
void quit()
{
	if (world)
		free_world(world);
	else
		free_area(local_area);
	set_color(RESET,BG RESET);
	set_canon(1);
	set_cursor_visible(1);
	exit(0);
}
void player_death()
{
	redraw(player);
	do {
		clear_announcements();
		announce("s","You have died.");
		announce("s","Press q to quit.");
		advance();
	} while (fgetc(stdin)!='q');
	next_line();
	quit();
}
