#ifndef ANNOUNCE_H
#define ANNOUNCE_H
#include <stdio.h>
#include <stdarg.h>
#include "area.h"
#include "entity.h"
#include "types.h"

void announce_stats(entity_t *);
void next_line();
void announce(char *, ...);
void clear_announcements();
#endif
