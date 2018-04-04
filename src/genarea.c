#include "genarea.h"
static inline color_t green() {
	return (rand()%2?GREEN:LGREEN);
}
static inline color_t gray() {
	return (rand()%2?DGRAY:LGRAY);
}
void place_tree(tile_t *area)
{
	int c=empty_coords(area);
	if (rand()%10) {
		area[c].fg='|';
		area[c].fg_c=BROWN;
	} else {
		area[c].fg='=';
		area[c].fg_c=BROWN;
	}
	area[c].bg='o';
	area[c].bg_c=BROWN;
}
void place_axe(tile_t *area)
{
	int c=inside_coords(area);
	area[c].fg='P';
	area[c].fg_c=WHITE;
}
AREA_TYPE(sand,"~~~___.,",8,
	symbol=='.'||symbol==','?BROWN:YELLOW,;)
AREA_TYPE(meadow,",.\'\'\"\"`;;*",10,
	symbol=='*'?YELLOW:(rand()%5?LGREEN:GREEN),;)
AREA_TYPE(field,",.\'`;",5,
	rand()%5?GREEN:LGREEN,;)
AREA_TYPE(sparse_grass,",.\'`;_",6,
		symbol=='_'?BROWN:green(),;)
AREA_TYPE(rock,".,*`:\"",6,
		symbol=='"'?green():gray(),;)
AREA_TYPE(snowy_rock,".,*`:",5,
		rand()%5?gray():WHITE,;)
AREA_TYPE(mountain,"-~~~_.",6,
		symbol=='.'?LGRAY:WHITE,;)
AREA_TYPE(forest,",.\'\"`;",6,
		symbol=='.'||symbol==','?gray():green(),
	int t=50+rand()%50;
	for (int i=0;i<t;i++)
		place_tree(area);
)

tile_t *generate_area(wtile_t *w)
{
	char map_symbol=w->symbol;
	color_t map_color=w->color;
	tile_t *area;
	switch (map_symbol) {
	case '~':
		switch (map_color) {
		case YELLOW:
			area=sand_gen();
			break;
		case LGREEN:
			area=meadow_gen();
			break;
		case GREEN:
			area=field_gen();
			break;
		default:
			area=NULL;
			break;
		}
		break;
	case '%':
		area=forest_gen();
		break;
	case '-':
		area=sparse_grass_gen();
		break;
	case '=':
		switch (map_color) {
		case LGRAY:
			area=rock_gen();
			break;
		case DGRAY:
			area=snowy_rock_gen();
			break;
		default:
			area=NULL;
			break;
		}
		break;
	case '^':
		area=mountain_gen();
		break;
	default:
		area=NULL;
		break;
	}
	if (w->elevation>50&&!(rand()%20)) {
		int r=10+rand()%20;
		for (int i=0;i<r;i++)
			random_room(area);
		fix_rooms(area);
		w->symbol='#';
		w->color=LRED;
		for (int i=0;i<r;i++)
			spawn_inside(area,&human_etype);
		if (rand()%2)
			place_axe(area);
	}
	return area;
}
