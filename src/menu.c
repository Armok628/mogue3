#include "menu.h"
static void draw_box(int off_x,int off_y,int width,int height)
{
	for (int x=1;x<width+1;x++)
		for (int y=1;y<height+1;y++)
			putc_pos(' ',x,y);
	for (int x=0;x<width+1;x++) {
		putc_pos('-',x,0);
		putc_pos('-',x,height+1);
	}
	for (int y=0;y<height+1;y++) {
		putc_pos('|',0,y);
		putc_pos('|',width+1,y);
	}
	putc_pos('/',0,0);
	putc_pos('\\',width+1,0);
	putc_pos('\\',0,height+1);
	putc_pos('/',width+1,height+1);
}
int menu(char **opts,int n_opts)
{
	if (n_opts<2)
		return 0;
	// Get max option length
	int maxl=0;
	for (int i=0;i<n_opts;i++) {
		int len=strlen(opts[i]);
		maxl=maxl>len?maxl:len;
	}
	// Draw box
	set_color(WHITE,BG BLACK);
	draw_box(0,0,maxl,n_opts);
	// Print options
	for (int o=0;o<n_opts;o++) {
		move_cursor(1,1+o);
		fputs(opts[o],stdout);
	}
	// Select option
	int index=0;
	int chosen=0;
	while (!chosen) {
		move_cursor(1,1+index);
		set_color(YELLOW,BG BLUE);
		fputs(opts[index],stdout);
		char input=fgetc(stdin);
		move_cursor(1,1+index);
		set_color(WHITE,BG BLACK);
		fputs(opts[index],stdout);
		switch (input) {
		case '2':
		case 'j':
			index+=index<n_opts-1;
			break;
		case '8':
		case 'k':
			index-=index>0;
			break;
		case 0:
		case 'q':
		case '\n':
			chosen++;
		}
	}
		// Redraw over menu
		for (int x=0;x<=maxl+1;x++)
			for (int y=0;y<=n_opts+1;y++)
				draw_pos(x,y);
		// Return selected value
		return index;
}
