#include "effects.h"
void add_entity_effect(entity_t *e,effect_t *eff,int dur)
{
	if (eff->type!=ENTITY)
		return;
	int c=0;
	for (;e->effects[c].dur;c++);
	e->effects[c].effect=eff;
	e->effects[c].dur=dur;
	if (eff->start)
		eff->start(e);
}
void handle_entity_eslot(entity_t *e,int slot)
{
	eslot_t *s=&e->effects[slot];
	if (s->dur) { // Duration < 0: Infinite
		s->dur-=s->dur>0;
		if (s->effect->turn)
			s->effect->turn(e);
	} else {
		s->dur=0;
		if (s->effect->end)
			s->effect->end(e);
		s->effect=NULL;
	}
}
void handle_entity_effects(entity_t *e)
{
	if (!e)
		return;
	for (int i=0;e->effects[i].effect;i++)
		handle_entity_eslot(e,i);
}
