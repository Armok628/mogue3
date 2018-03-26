#ifndef SPELLS_H
#define SPELLS_H
#include <stdlib.h>
#include "entity.h"
#include "announce.h"

#define SPELL(name) void name(entity_t *caster)
#define SPELL_START(cname,rname) \
char *cname##_name=#rname; \
SPELL(cname) { entity_t *target=
#define ON(target) target;
#define SPELL_END }

SPELL(heal_self);
#endif
