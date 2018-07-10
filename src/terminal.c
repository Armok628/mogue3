#include "terminal.h"
void move_cursor(int x,int y)
{
	printf("\033[%d;%dH",y+1,x+1);
}
void putc_pos(char ch,int x,int y)
{
	move_cursor(x,y);
	putchar(ch);
}
void clear_screen()
{
	set_color(RESET,BG RESET);
	fputs("\033[2J",stdout);
}
void clear_line()
{
	set_color(RESET,BG RESET);
	fputs("\033[2K",stdout);
}
void set_cursor_visible(int v)
{
	printf("\033[?25%c",v?'h':'l');
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
void set_blocking(int b)
{
	struct termios term;
	tcgetattr(0,&term);
	if (b)
		term.c_cc[VMIN]=1;
	else
		term.c_cc[VMIN]=0;
	tcsetattr(0,TCSANOW,&term);
}
void set_color(color_t c,color_t bg)
{
	printf("\033[%d;%d;%dm",c/100,c%100,bg);
}
int get_cursor_pos(int xf,int yf)
{
	struct termios term;
	tcgetattr(0,&term);
	set_canon(0);
	set_blocking(1);
	int x,y;
	printf("\033[6n");
	fscanf(stdin,"\033[%d;%dH",&y,&x);
	tcsetattr(0,TCSANOW,&term);
	return (x-1)*xf+(y-1)*yf;
}
