#ifndef _PHYSICS_H
#define _PHYSICS_H

#include "main.h"

int  updateCreature(double dt, Flyvende *vesen);
void setSpeed(Prosjektil *p, Towerman *t);
// int  pro_offBoard(Prosjektil *p, Towerman *t);
int  fly_offBoard(Flyvende *vesen);
void updateProjectiles(double dt, Towerman *t, BITMAP *colmap);
void updateTowerman(double dt, Towerman *t);
void updateDucks(double dt, Ducks *d);
void putOnCol(Flyvende *vesen, int nr, BITMAP *colmap);

#endif
