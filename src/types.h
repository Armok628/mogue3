#ifndef TYPES_H
#define TYPES_H
#include "terminal.h" // color_t
#define INV_SIZE 16  // TODO: Define quantities in better terms; add range checking

// TODO: Split back into respective files or find compromise

typedef enum {false,true} bool;
typedef enum {PERSISTS=1,SOLID=1<<1,MOBILE=1<<2} eflag_t;// e(ntity)flag
typedef enum {
	NONE=0,
	WILDERNESS=1,
	TOWN=1<<1,
	DUNGEON=1<<2,
	INSIDE=1<<3,
	OUTSIDE=1<<4
} sflag_t; // s(pawn)flag
typedef enum {NORTH,SOUTH,EAST,WEST} dir_t; // dir(ection)
typedef enum {OFFENSE,DEFENSE,UTILITY} cat_t; // cat(egory)

typedef struct entity_s entity_t;

// Items
typedef struct itype_s { // TODO: Maximum stack size
	char *name;
	cat_t category;
	int effect;
	int value;
	char symbol;
	color_t color;
	void (*use)(entity_t *);
} itype_t; // i(tem)type
typedef struct islot_s {
	itype_t *type;
	int count;
} islot_t; // i(tem)slot
typedef struct ltab_s {
	int count;
	itype_t *items[INV_SIZE];
	int amounts[INV_SIZE];
	int chances[INV_SIZE]; // Percentages
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
	spell_t *spells[INV_SIZE];
	struct etype_s *friends[INV_SIZE];
	struct etype_s *enemies[INV_SIZE];
	eflag_t flags;
	ltab_t loot_table;
	sflag_t spawn_flags;
	int min_elev,max_elev;
	int min_sp,max_sp;
} etype_t; // e(ntity)type
struct entity_s {
	char *name,symbol;
	color_t color;
	int coords; // coords can be used by spells
	spell_t *spells[INV_SIZE];
	int hp,maxhp,res,agi,wis,str;
	eflag_t flags;
	etype_t *type;
	islot_t inventory[INV_SIZE];
	islot_t equipped[INV_SIZE];
};

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
	islot_t pile[INV_SIZE];
} tile_t;
typedef struct wtile_s {
	tile_t *area;
	int elevation;
	char symbol;
	color_t color;
	bool town,landing;
} wtile_t; // w(orld)tile
#endif
