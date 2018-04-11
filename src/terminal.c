#include "terminal.h"
void move_cursor(int x,int y)
{
	printf("\e[%d;%dH",y+1,x+1);
}
void putc_pos(char ch,int x,int y)
{
	move_cursor(x,y);
	putchar(ch);
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
	printf("\e[?25%c",v?'h':'l');
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
int cursor_pos(int xf,int yf)
{
	int x,y;
	printf("\e[6n");
	fscanf(stdin,"\e[%d;%dH",&y,&x);
	return (x-1)*xf+(y-1)*yf;
}
