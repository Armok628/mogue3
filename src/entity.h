#ifndef ENTITY_H
#define ENTITY_H
#include <stdlib.h>
#include "terminal.h"
typedef struct tile_s tile_t;
#include "area.h"
typedef struct spell_s spell_t;
#include "spells.h"
#include "bool.h"
typedef enum {PERSISTS=1,SOLID=1<<1} eflag_t; // TODO: More properties
typedef struct etype_s {
	char *name,symbol;
	color_t color;
	int minhp,maxhp;
	int minstr,maxstr;
	int minwis,maxwis;
	spell_t *spells[16];
	int spellc;
	eflag_t flags;
} etype_t;
typedef struct entity_s {
	char *name,symbol;
	color_t color;
	int coords,spellc; // coords can be used by spells
	spell_t *spells[16];
	int hp,maxhp,str,wis;
	eflag_t flags;
	etype_t *type;
} entity_t;

extern etype_t player_etype;
extern etype_t human_etype;
extern etype_t monster_etype;
extern entity_t *player;

void draw_entity(entity_t *);
void redraw(entity_t *);
entity_t *spawn(etype_t *);
entity_t *spawn_randomly(tile_t *area,etype_t *);
entity_t *spawn_inside(tile_t *area,etype_t *);
entity_t *spawn_outside(tile_t *area,etype_t *);
#endif
