#include "announce.h"
static int ann_lines=0;
void next_line()
{
	move_cursor(0,HEIGHT+ann_lines);
}
void announce_stats(entity_t *e)
{
	announce("s e s dsd s d s d"
			,e->name,e,
			"HP:",e->hp,"/",e->maxhp,
			"STR:",e->str,
			"WIS:",e->wis);
}
void announce(char *fmt, ...)
{
	va_list ap;
	int d;
	entity_t *e;
	char *s;
	va_start(ap,fmt);
	move_cursor(0,HEIGHT+ann_lines);
	set_color(RESET,BG RESET);
	for (;*fmt;fmt++) {
		switch (*fmt) {
		case 's':
			s=va_arg(ap,char *);
			fputs(s,stdout);
			break;
		case 'e':
			e=va_arg(ap,entity_t *);
			draw_entity(e);
			set_color(RESET,BG RESET);
			break;
		case 'd':
			d=va_arg(ap,int);
			printf("%d",d);
			break;
		case ' ':
			putchar(' ');
		}
	}
	va_end(ap);
	ann_lines++;
}
void clear_announcements()
{
	for (int i=HEIGHT;i<HEIGHT+ann_lines;i++) {
		move_cursor(0,i);
		clear_line();
	}
	ann_lines=0;
}
