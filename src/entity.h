#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include "terminal.h"
typedef struct tile_s tile_t;
#include "area.h"
typedef struct spell_s spell_t;
#include "spells.h"
typedef enum {false,true} bool;
typedef enum {PERSISTS=1,SOLID=1<<1} eflag_t; // TODO: More properties
typedef struct entity_s {
	char *name,symbol;
	color_t color;
	int coord,spellc; // coord can be used by spells
	spell_t *spells[16];
	int hp,maxhp,str,wis;
	eflag_t flags;
} entity_t;
typedef struct etype_s {
	char *name,symbol;
	color_t color;
	int minhp,maxhp;
	int minstr,maxstr;
	int minwis,maxwis;
	eflag_t flags;
} etype_t;

extern etype_t playertype;
extern etype_t monstertype;
extern entity_t *player;

void draw_entity(entity_t *);
entity_t *make_entity(etype_t *);
entity_t *place_randomly(etype_t *);
void cast(entity_t *,int);
#endif
