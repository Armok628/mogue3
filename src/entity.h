#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include "terminal.h"
typedef enum {false,true} bool;
typedef struct entity_s {
	char *name,symbol;
	color_t color;
	int coord,spellc; // coord can be used by spells
	void (*spells[16])(struct entity_s *); // oof
	char *spellnames[16];
	int hp,maxhp,str,wis;
} entity_t;
typedef struct etype_s {
	char *name,symbol;
	color_t color;
	int minhp,maxhp;
	int minstr,maxstr;
	int minwis,maxwis;
} etype_t;

extern etype_t playertype;
extern entity_t *player;

void draw_entity(entity_t *);
entity_t *make_entity(etype_t *);
void cast(entity_t *,int);
#endif
