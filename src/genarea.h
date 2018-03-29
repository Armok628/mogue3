#ifndef GENAREA_H
#define GENAREA_H
#include "world.h"
#include "area.h"

#define AREA_TYPE(land,symbols,nsyms,colors) \
char land##_s[nsyms]=symbols; \
tile_t *land##_gen() \
{ \
	tile_t *area=malloc(AREA*sizeof(tile_t)); \
	for (int i=0;i<AREA;i++) { \
		char symbol=land##_s[rand()%nsyms]; \
		area[i].fg='\0'; \
		area[i].fg_c=BLACK; \
		area[i].bg=symbol; \
		area[i].bg_c=colors; \
		area[i].e=NULL; \
		area[i].corpse=NULL; \
	} \
	return area; \
}

tile_t *generate_area(char,color_t);
#endif
