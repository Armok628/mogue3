#ifndef TYPES_H
#define TYPES_H
#include <stdlib.h>
#include "terminal.h" // color_t
#define INV_SIZE 16  // TODO: Define quantities in better terms; add range checking

// TODO: Split back into respective files or find compromise

typedef enum {false,true} bool;
typedef enum {
	PERSISTS=1,
	SOLID=1<<1,
	MOBILE=1<<2,
	USES_ITEMS=1<<3,
	CASTS_SPELLS=1<<4,
} eflag_t;// e(ntity)flag
typedef enum {
	NONE=0,
	WILDERNESS=1,
	TOWN=1<<1,
	DUNGEON=1<<2,
	INSIDE=1<<3,
	OUTSIDE=1<<4,
} sflag_t; // s(pawn)flag
typedef enum {NORTH,SOUTH,EAST,WEST} dir_t; // dir(ection)
typedef enum {OFFENSE,DEFENSE,UTILITY} cat_t; // cat(egory)

typedef struct entity_s entity_t;
typedef struct tile_s tile_t;

typedef int range_t[2];
static inline int ranged_rand(range_t r)
{
	return r[0]+rand()%(1+r[1]-r[0]);
}
static inline int enforce_range(int i,range_t r)
{
	return r[1]>i?r[0]>i?r[0]:i:r[1];
}
static inline bool in_range(int i,range_t r)
{
	return r[0]<=i&&i<=r[1];
}

typedef struct freq_s {
	int chance;
	range_t counts;
	range_t times;
} freq_t;

// Effects
typedef struct effect_s {
	void (*start)(int);
	void (*turn)(int);
	void (*end)(int);
} effect_t;
typedef struct eslot_s {
	int dur;
	effect_t *effect;
} eslot_t; // e(ffect)slot

// Items
typedef struct itype_s { // TODO: Maximum stack size
	char *name;
	cat_t category;
	int effect;
	int value;
	char symbol;
	color_t color;
	void (*use)(entity_t *);
	sflag_t spawn_flags;
	range_t elev;
	freq_t freq;
} itype_t; // i(tem)type
typedef struct islot_s {
	itype_t *type;
	int count;
} islot_t; // i(tem)slot
typedef struct ltslot_s { //l(oot)t(able)slot
	itype_t *type;
	freq_t freq;
} ltslot_t;
typedef ltslot_t ltab_t[INV_SIZE]; // l(oot)tab(le)

// Entities
typedef struct spell_s spell_t;
typedef struct etype_s {
	char *name,symbol;
	color_t color;
	range_t hp;
	range_t res;
	range_t agi;
	range_t wis;
	range_t str;
	spell_t *spells[INV_SIZE];
	struct etype_s *friends[INV_SIZE];
	struct etype_s *enemies[INV_SIZE];
	eflag_t flags;
	ltab_t loot_table;
	effect_t *perm_effects[INV_SIZE];
	sflag_t spawn_flags;
	range_t elev;
	freq_t freq;
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
	eslot_t effects[INV_SIZE];
};

// Spells
typedef struct spell_s {
	void (*function)(entity_t *);
	char *name;
	cat_t category;
} spell_t;

// Tiles
struct tile_s {
	entity_t *e,*corpse;
	color_t fg_c,bg_c;
	char fg,bg;
	islot_t pile[INV_SIZE];
	eslot_t effects[INV_SIZE];
};
typedef struct wtile_s {
	tile_t *area;
	int elevation;
	char symbol;
	color_t color;
	bool town,landing;
} wtile_t; // w(orld)tile

#endif
