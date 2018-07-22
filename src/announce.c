#include "announce.h"
static int ann_lines=0;
void next_line()
{
	move_cursor(0,HEIGHT+ann_lines++);
}
void print_stats(entity_t *e)
{
	if (replay!=stdin)
		return;
	set_color(RESET,BG RESET);
	printf("%s ",e->name);
	draw_entity(e);
	set_color(RESET,BG RESET);
	printf(" %s %d%s%d %s %d %s %d %s %d %s %d",
			"HP:",e->hp,"/",e->maxhp,
			"RES:",e->res,
			"AGI:",e->agi,
			"WIS:",e->wis,
			"STR:",e->str);
}
void announce_stats(entity_t *e)
{
	next_line();
	print_stats(e);
}
void announce(char *fmt, ...)
{
	if (replay!=stdin)
		return;
	va_list ap;
	int d;
	entity_t *e;
	char *s;
	va_start(ap,fmt);
	next_line();
	set_color(RESET,BG RESET);
	for (;*fmt;fmt++) {
		switch (*fmt) {
		case 's':
			s=va_arg(ap,char *);
			fputs(s,stdout);
			break;
		case 'e':
			e=va_arg(ap,entity_t *);
			if (e->flags&PERSISTS) {
				printf("%s (",e->name);
				draw_entity(e);
				set_color(RESET,BG RESET);
				putchar(')');
			} else {
				draw_entity(e);
				set_color(RESET,BG RESET);
			}
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
}
void clear_announcements()
{
	for (int i=HEIGHT;i<HEIGHT+ann_lines;i++) {
		move_cursor(0,i);
		clear_line();
	}
	ann_lines=0;
}
