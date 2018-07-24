#ifndef TERMINAL_H
#define TERMINAL_H
#include "stdio.h"
#include "termios.h"

#define FG 100*
#define BG +10+

typedef enum {
	BLACK=30,RED,GREEN,BROWN,BLUE,PURPLE,CYAN,L_GRAY,RESET,
	D_GRAY=130,L_RED,L_GREEN,YELLOW,L_BLUE,PINK,L_CYAN,WHITE,
} color_t;

void move_cursor(int,int);
void putc_pos(char,int,int);
void clear_screen();
void clear_line();
void set_cursor_visible(int);
void set_canon(int);
void set_blocking(int);
void set_color(color_t);
int get_cursor_pos(int,int);
#endif
