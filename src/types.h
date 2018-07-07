#ifndef TYPES_H
#define TYPES_H
#include "terminal.h" // color_t

typedef enum {false,true} bool;
typedef enum {PERSISTS=1,SOLID=1<<1,MOBILE=1<<2} eflag_t;// e(ntity)flag
// TODO: Entity effects (burning, regenerating, etc.)
typedef enum {NORTH,SOUTH,EAST,WEST} dir_t; // dir(ection)
typedef enum {OFFENSE,DEFENSE,UTILITY} cat_t; // cat(egory)

// Items
typedef struct itype_s {
	char *name;
	cat_t category;
	int effect;
	int value;
	char symbol;
	color_t color;
} itype_t; // i(tem)type
typedef struct islot_s {
	itype_t *type;
	int count;
} islot_t; // i(tem)slot
typedef struct ltab_s {
	int count;
	itype_t *items[16];
	int amounts[16];
	int chances[16]; // Percentages
} ltab_t; // l(oot)tab(le)

// Entities
typedef struct spell_s spell_t;
typedef struct etype_s {
	char *name,symbol;
	color_t color;
	int minhp,maxhp;
	int minres,maxres;
	int minagi,maxagi;
	int minwis,maxwis;
	int minstr,maxstr;
	spell_t *spells[16];
	struct etype_s *friends[16];
	struct etype_s *enemies[16];
	eflag_t flags;
	ltab_t loot_table;
} etype_t; // e(ntity)type
typedef struct entity_s {
	char *name,symbol;
	color_t color;
	int coords; // coords can be used by spells
	spell_t *spells[16];
	int hp,maxhp,res,agi,wis,str;
	eflag_t flags;
	etype_t *type;
	islot_t inventory[16];
	islot_t equipped[5];
} entity_t;

// Spells
typedef struct spell_s {
	void (*function)(entity_t *);
	char *name;
	cat_t category;
} spell_t;

// Tiles
typedef struct tile_s {
	entity_t *e,*corpse;
	color_t fg_c,bg_c;
	char fg,bg;
	islot_t pile[16];
} tile_t;
typedef struct wtile_s {
	tile_t *area;
	int elevation;
	char symbol;
	color_t color;
	bool city,landing;
} wtile_t; // w(orld)tile
#endif
