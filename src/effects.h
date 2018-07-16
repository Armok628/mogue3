#ifndef EFFECTS_H
#define EFFECTS_H
#include "area.h"
#include "types.h"

void add_effect(eslot_t [],effect_t *,int,int);
void remove_effect_slot(eslot_t [],int);
void handle_effect_slot(int,eslot_t [],int);
void handle_entity_effects(entity_t *);
void handle_tile_effects(int);
void end_effect(eslot_t [],effect_t *,int);
#endif
