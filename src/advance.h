#ifndef ADVANCE_H
#define ADVANCE_H
#include "area.h"
#include "effects.h"
#include "entity.h"
#include "input.h"
#include "inventory.h"
#include "map.h"
#include "move.h"
#include "think.h"

void handle_input(entity_t *,char);
void take_turn(entity_t *e);
void advance();
#endif
