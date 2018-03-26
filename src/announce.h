#ifndef ANNOUNCE_H
#define ANNOUNCE_H
#include <stdio.h>
#include <stdarg.h>
#include "entity.h"
#include "area.h"

void announce_stats(entity_t *);
void next_line();
void announce(char *, ...);
void clear_announcements();
#endif
