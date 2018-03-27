#ifndef WORLD_H
#define WORLD_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "terminal.h"
#define W_WIDTH 80
#define W_HEIGHT 24
#define W_AREA (W_WIDTH*W_HEIGHT)

int avg_elev(int l[W_WIDTH][W_HEIGHT],int x,int y);
void erode(int land[W_WIDTH][W_HEIGHT]);
color_t elevation_color(int elevation);
char elevation_symbol(int elevation);
void draw_land(int land[W_WIDTH][W_HEIGHT]);
void elevate(int land[W_WIDTH][W_HEIGHT],int offset);
#endif
