#include "genarea.h"
static inline color_t green() {
	return (rand()%2?GREEN:L_GREEN);
}
static inline color_t gray() {
	return (rand()%2?D_GRAY:L_GRAY);
}
void place_tree(tile_t *area)
{
	int c=empty_coords(area);
	area[c].fg='|';
	area[c].fg_c=BROWN;
	area[c].bg='o';
	area[c].bg_c=BROWN;
}
void place_trees(tile_t *area,int n)
{
	for (int i=0;i<n;i++)
		place_tree(area);
}
void place_spike(tile_t *area,color_t color)
{
	int c=empty_coords(area);
	area[c].bg='^';
	area[c].bg_c=color;
}
void place_boulder(tile_t *area)
{
	int c=empty_coords(area);
	area[c].fg='O';
	area[c].fg_c=D_GRAY;
}
void place_boulders(tile_t *area,int n)
{
	for (int i=0;i<n;i++)
		place_boulder(area);
}
AREA_TYPE(sand,"~~~___.,",8,
	symbol=='.'||symbol==','?BROWN:YELLOW,;)
AREA_TYPE(meadow,",.\'\'\"\"`;;*",10,
	symbol=='*'?YELLOW:(rand()%5?L_GREEN:GREEN),
	place_trees(area,rand()%5); // 0-4 trees
)
AREA_TYPE(field,",.\'`;",5,
	rand()%5?GREEN:L_GREEN,
	place_trees(area,rand()%25); // 0-24 trees
)
AREA_TYPE(sparse_grass,",.\'`;_",6,
		symbol=='_'?BROWN:green(),;)
AREA_TYPE(rock,".,*`:\"",6,
		symbol=='"'?green():gray(),
		place_boulders(area,rand()%15);
		int n=rand()%10;
		for (int i=0;i<n;i++)
			place_spike(area,gray());
)
AREA_TYPE(snowy_rock,".,*`:",5,
		rand()%5?gray():WHITE,
		place_boulders(area,rand()%10);
		int n=rand()%10;
		for (int i=0;i<n;i++)
			place_spike(area,rand()%2?D_GRAY:WHITE);
)
AREA_TYPE(mountain,"-~~~_.",6,
		symbol=='.'?L_GRAY:WHITE,
		place_boulders(area,rand()%5);
		int n=rand()%20;
		for (int i=0;i<n;i++)
			place_spike(area,L_CYAN);
)
AREA_TYPE(forest,",.\'\"`;",6,
		symbol=='.'||symbol==','?gray():green(),
	place_trees(area,50+rand()%50); // 50-99 trees
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
		case L_GREEN:
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
		case L_GRAY:
			area=rock_gen();
			break;
		case D_GRAY:
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
	}
	if (!area)
		return NULL;
	if (w->town) {
		int r=10+rand()%20;
		for (int i=0;i<r;i++)
			random_room(area);
		fix_rooms(area);
		int c=inside_coords(area);
		area[c].bg='>';
		area[c].bg_c=BROWN;
	}
	populate(w,area,true);
	spawn_loot(w,area);
	return area;
}
void wallify(tile_t *t)
{
	t->fg=t->bg;
	t->fg_c=t->bg_c;
}
AREA_TYPE(dungeon," ",1,gray(), // Note: ' ' is not nothing
	for (int i=0;i<AREA;i++)
		wallify(&area[i]);
	for (int i=0;i<AREA/96;i++)
		random_room(area);
	fix_rooms(area);
	for (int i=0;i<AREA/384;i++)
		random_path(area);
	spawn_loot(NULL,area);
)
