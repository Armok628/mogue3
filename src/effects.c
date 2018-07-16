#include "effects.h"
void add_effect(eslot_t s[],effect_t *e,int dur,int coords)
{
	int c=0;
	for (;s[c].effect;c++);
	s[c].effect=e;
	s[c].dur=dur;
	if (e->start)
		e->start(coords);
}
void remove_effect_slot(eslot_t effects[],int slot)
{
	if (slot<0)
		return;
	int c=0;
	for (;effects[c].effect;c++);
	if (c<=slot)
		return;
	effects[slot]=effects[c-1];
	effects[c-1].effect=NULL;
	effects[c-1].dur=0;
}
void handle_effect_slot(int coords,eslot_t effects[],int slot)
{
	eslot_t *s=&effects[slot];
	if (s->dur) { // Duration < 0: Infinite
		s->dur-=s->dur>0;
		if (s->effect->turn)
			s->effect->turn(coords);
	} else {
		if (s->effect->end)
			s->effect->end(coords);
		remove_effect_slot(effects,slot);
	}
}
void handle_entity_effects(entity_t *e)
{
	for (int i=0;e->effects[i].effect;i++)
		if (e->hp)
			handle_effect_slot(e->coords,e->effects,i);
}
void handle_tile_effects(int c)
{
	eslot_t *s=local_area[c].effects;
	for (int i=0;s[i].effect;i++)
		handle_effect_slot(c,s,i);
}
