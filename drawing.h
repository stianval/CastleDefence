#ifndef _DRAWING_H
#define _DRAWING_H

#include "main.h"

void drawTowerman();
void draw(Flyvende *vesen, BITMAP *backbuffer);
void draw_ducks(BITMAP *duck, BITMAP *backbuffer, Ducks *d);
void draw_p(Prosjektil *p, BITMAP *backbuffer);
void draw_text(BITMAP *source, BITMAP *backbuffer, int x, int y, int x_frame,int y_frame,char *text);
void draw_t(Towerman *vesen, BITMAP *backbuffer);
void draw_cross(Towerman *t, BITMAP *cross, BITMAP *backbuffer);
void draw_exp(Prosjektil *p, BITMAP *explotion, BITMAP *backbuffer);

#endif
