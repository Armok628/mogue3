#ifndef SPELLS_H
#define SPELLS_H
#include <stdlib.h>
typedef struct entity_s entity_t;
#include "announce.h"
#include "entity.h"
#include "menu.h"
#include "target.h"

#define SPELL(name) \
extern spell_t name##_spell; \
void name(entity_t *caster);

#define SPELL_START(cname,sname,stype) \
void cname(entity_t *); \
spell_t cname##_spell={ \
	.function=&cname, \
	.name=#sname, \
	.type=stype \
}; \
void cname(entity_t *caster) \
{

#define ON(t) entity_t *target=t;

#define SPELL_END }

typedef enum {DEFENSE,OFFENSE} spelltype_t;
typedef struct spell_s {
	void (*function)(entity_t *);
	char *name;
	spelltype_t type;
} spell_t;

void cast(entity_t *,int);
void spell_menu(entity_t *);
SPELL(heal_self);
SPELL(magic_missile);
SPELL(raise_dead);
#endif
