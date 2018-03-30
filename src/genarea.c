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
	area[c].fg='|';
	area[c].fg_c=BROWN;
}
AREA_TYPE(empty_void," ",1,
	BLACK,;)
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
	for (int i=0;i<100;i++)
		place_tree(area);
)

tile_t *generate_area(char map_symbol,color_t map_color)
{
	switch (map_symbol) {
	case '~':
		switch (map_color) {
		case YELLOW:
			return sand_gen();
		case LGREEN:
			return meadow_gen();
		case GREEN:
			return field_gen();
		default:
			return empty_void_gen();
		}
	case '%':
		return forest_gen();
	case '-':
		return sparse_grass_gen();
	case '=':
		switch (map_color) {
		case LGRAY:
			return rock_gen();
		case DGRAY:
			return snowy_rock_gen();
		default:
			return empty_void_gen();
		}
	case '^':
		return mountain_gen();
	default:
		return empty_void_gen();
	}
}
