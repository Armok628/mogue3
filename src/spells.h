#ifndef SPELLS_H
#define SPELLS_H
#include <stdlib.h>
typedef struct entity_s entity_t;
#include "entity.h"
#include "announce.h"

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
{ \
	entity_t *target=

#define ON(target) target;

#define SPELL_END }

typedef enum {DEFENSE,OFFENSE} spelltype_t;
typedef struct spell_s {
	void (*function)(entity_t *);
	char *name;
	spelltype_t type;
} spell_t;

SPELL(heal_self);
#endif
