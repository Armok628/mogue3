#include "target.h"
bool visible(int c1,int c2)
{
	float x1=xcmp(c1),x2=xcmp(c2);
	float y1=ycmp(c1),y2=ycmp(c2);
	float d_x=x2-x1,d_y=y2-y1;
	float mag=sqrt(d_x*d_x+d_y*d_y);
	float dx=d_x/mag,dy=d_y/mag;
	for (float d=0;d<mag;d+=1) {
		int x=round(x1+=dx);
		int y=round(y1+=dy);
		tile_t *t=&local_area[lin(x,y)];
		if (x==x2&&y==y2)
			return true;
		if (t->fg||t->e)
			return false;
		//set_color(WHITE,BG BLACK);
		//putc_pos('#',x,y);
	}
	return true;
}
int player_target()
{
	int c=player->coords;
	char input;
	clear_announcements();
	do {
		set_color(YELLOW,BG BLACK);
		putc_pos('X',xcmp(c),ycmp(c));
		if (local_area[c].e)
			announce_stats(local_area[c].e);
		input=fgetc(stdin);
		draw_posl(c);
		c+=input_offset(input);
		clear_announcements();
	} while (input!='\n'&&input!='q');
	clear_announcements();
	return c;
}
int target_by(entity_t *caster)
{
	if (caster==player)
		return player_target();
	return rand()%AREA; // Temporary
}
