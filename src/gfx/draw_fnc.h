#pragma once

#include "draw.h"

void line(vec2 p0, vec2 p1);
void drawrect(int x, int y, int w, int h);
void drawrect(vec2 pos, vec2 dim);
void fillrect(int x, int y, int w, int h);
void fillrect(vec2 pos, vec2 dim);
void setcolor(int r, int g, int b, int a = SDL_ALPHA_OPAQUE);
void dotted_line(vec2 p0, vec2 p1, int space);
