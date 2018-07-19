#ifndef INPUT_H
#define INPUT_H
#include "actions.h"
#include "area.h"
#include "debug.h"
#include "quit.h"
#include "target.h"
extern FILE *replay;
extern FILE *record;

char get_input();
int input_offset(char);
char offset_input(int);
char generate_input();
char *string_prompt(char *);
int int_prompt(char *);
#endif
