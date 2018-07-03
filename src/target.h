#ifndef TARGET_H
#define TARGET_H
#include <math.h>
#include "area.h"
#include "input.h"
#include "terminal.h"
#include "types.h"

bool visible(int,int);
int player_target();
bool friend(entity_t *,entity_t *);
bool enemy(entity_t *,entity_t *);
entity_t *target_friend(entity_t *);
entity_t *target_enemy(entity_t *);
#endif
