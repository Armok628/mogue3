#ifndef TERMINAL_H
#define TERMINAL_H
#include "stdio.h"
#include "termios.h"

#define BG 10+

typedef enum {
	BLACK=30,RED,GREEN,BROWN,BLUE,PURPLE,CYAN,LGRAY,RESET,
	DGRAY=130,LRED,LGREEN,YELLOW,LBLUE,LPURPLE,LCYAN,WHITE
} color_t;

void move_cursor(int,int);
void putc_pos(char,int,int);
void clear_screen();
void clear_line();
void set_cursor_visible(int);
void set_canon(int);
void set_color(color_t,color_t);
#endif
