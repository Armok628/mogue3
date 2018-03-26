#include "quit.h"
void quit()
{
	for (int i=0;i<AREA;i++)
		if (area[i].e)
			free(area[i].e);
	set_color(RESET,BG RESET);
	set_canon(1);
	set_cursor_visible(1);
	next_line();
	exit(0);
}
