#ifndef GENAREA_H
#define GENAREA_H
#include "area.h"
#include "populate.h"
#include "room.h"
#include "world.h"

#define AREA_TYPE(land,symbols,nsyms,colors,extras) \
char land##_s[nsyms]=symbols; \
tile_t *land##_gen() \
{ \
	tile_t *area=calloc(AREA,sizeof(tile_t)); \
	for (int i=0;i<AREA;i++) { \
		char symbol=land##_s[rand()%nsyms]; \
		area[i].fg='\0'; \
		area[i].fg_c=BLACK; \
		area[i].bg=symbol; \
		area[i].bg_c=colors; \
		area[i].pile[0].count=0; \
		area[i].e=NULL; \
		area[i].corpse=NULL; \
	} \
	extras \
	return area; \
}

tile_t *generate_area(wtile_t *);
tile_t *dungeon_gen(); // Made with AREA_TYPE(dungeon,...)
#endif
