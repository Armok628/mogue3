#include "terminal.h"
void move_cursor(int x,int y)
{
	printf("\e[%d;%dH",y+1,x+1);
}
void clear_screen()
{
	set_color(RESET,BG RESET);
	fputs("\e[2J",stdout);
}
void clear_line()
{
	set_color(RESET,BG RESET);
	fputs("\e[2K",stdout);
}
void set_cursor_visible(int v)
{
	fputs(v?"\e[?25h":"\e[?25l",stdout);
}
void set_canon(int c)
{
	struct termios term;
	tcgetattr(0,&term);
	if (c)
		term.c_lflag|=(ICANON|ECHO);
	else
		term.c_lflag&=~(ICANON|ECHO);
	tcsetattr(0,TCSANOW,&term);
}
void set_color(color_t c,color_t bg)
{
	printf("\e[%d;%d;%dm",c/100,c%100,bg);
}
