#ifndef TYPES_H
#define TYPES_H
#include "terminal.h"
typedef enum {false,true} bool;
typedef enum {PERSISTS=1,SOLID=1<<1} eflag_t; // TODO: More properties
typedef enum {NORTH,SOUTH,EAST,WEST} dir_t;
typedef enum {DEFENSE,OFFENSE} spelltype_t;
typedef struct spell_s spell_t;
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
typedef struct spell_s {
	void (*function)(entity_t *);
	char *name;
	spelltype_t type;
} spell_t;
typedef struct tile_s {
	entity_t *e,*corpse;
	color_t fg_c,bg_c;
	char fg,bg;
} tile_t;
typedef struct wtile_s {
	tile_t *area;
	int elevation;
	char symbol;
	color_t color;
	bool city,landing;
} wtile_t;
#endif
