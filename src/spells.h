#ifndef SPELLS_H
#define SPELLS_H
#include <stdlib.h>
#include "announce.h"
#include "entity.h"
#include "menu.h"
#include "target.h"
#include "types.h"

#define SPELL(name) \
extern spell_t name##_spell; \
void name(entity_t *caster);

#define SPELL_START(cname,sname,cat) \
void cname(entity_t *); \
spell_t cname##_spell={ \
	.function=&cname, \
	.name=#sname, \
	.category=cat \
}; \
void cname(entity_t *caster) \
{

#define ON(t) entity_t *target=t;

#define SPELL_END }

void cast(entity_t *,int);
void spell_menu(entity_t *);
void random_spell(entity_t *);
SPELL(heal_self)
SPELL(magic_missile)
SPELL(raise_dead)
SPELL(freeze)
SPELL(thaw)
SPELL(dragonfire)
#endif
