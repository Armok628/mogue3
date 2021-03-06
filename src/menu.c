#include "menu.h"
static void draw_box(int off_x,int off_y,int width,int height)
{
	for (int x=1;x<width+1;x++)
		for (int y=1;y<height+1;y++)
			putc_pos(' ',off_x+x,off_y+y);
	for (int x=0;x<width+1;x++) {
		putc_pos('-',off_x+x,off_y+0);
		putc_pos('-',off_x+x,off_y+height+1);
	}
	for (int y=0;y<height+1;y++) {
		putc_pos('|',off_x+0,off_y+y);
		putc_pos('|',off_x+width+1,off_y+y);
	}
	putc_pos('/',off_x+0,off_y+0);
	putc_pos('\\',off_x+width+1,off_y+0);
	putc_pos('\\',off_x+0,off_y+height+1);
	putc_pos('/',off_x+width+1,off_y+height+1);
}
int menu_at_pos(char **opts,int n_opts,int off_x,int off_y) // TODO: Fix ugly goto structure. Refactor
{ // Sentinel value -1 for no choice
	if (n_opts<1)
		return -1;
	int index=0;
	bool chosen=false;
	int maxl=0;
	if (replay!=stdin)
		goto MENU_CONTROL_LOOP;
	// Get max option length
	for (int i=0;i<n_opts;i++) {
		int len=strlen(opts[i]);
		maxl=maxl>len?maxl:len;
	}
	// Draw box
	set_color(FG WHITE BG BLACK);
	draw_box(off_x,off_y,maxl,n_opts);
	// Print options
	for (int o=0;o<n_opts;o++) {
		move_cursor(off_x+1,off_y+1+o);
		fputs(opts[o],stdout);
	}
	// Select option
MENU_CONTROL_LOOP:
	for (;;) {
		char input;
		if (replay!=stdin) {
			input=get_input();
			goto MENU_KEY_CASE;
		}
		move_cursor(off_x+1,off_y+1+index);
		set_color(FG YELLOW BG BLUE);
		fputs(opts[index],stdout);
		input=get_input();
		move_cursor(off_x+1,off_y+1+index);
		set_color(FG WHITE BG BLACK);
		fputs(opts[index],stdout);
MENU_KEY_CASE:
		switch (input) {
		case '2':
		case 'j':
			index=index>=n_opts-1?0:index+1;
			continue;
		case '8':
		case 'k':
			index=index<=0?n_opts-1:index-1;
			continue;
		case '\n':
			chosen=true;
		case 'q':
		case 27: // '\e'
			goto MENU_REDRAW;
		}
	}
MENU_REDRAW:
	if (replay!=stdin)
		goto MENU_RETURN;
	// Redraw over menu
	for (int x=0;x<=maxl+1;x++)
		for (int y=0;y<=n_opts+1;y++)
			draw_pos(off_x+x,off_y+y);
	// Return selected value
MENU_RETURN:
	return chosen?index:-1;
}
int menu(char **opts,int n_opts)
{
	return menu_at_pos(opts,n_opts,1,1);
}
