#ifndef _STORAGE_H
#define _STORAGE_H

#include "main.h"

void defFlying(Flyvende *vesen,
			   // int maksvx // ?
			   // int maksxy // ?
			   int     life,
			   int     antFrames,
			   int     score,
			   BITMAP *sprite);

void posFlying(Flyvende *vesen, int x, int y, int vx, int vy, int type);
void createTowerman(Towerman *t, int maxShoots, int frames, int strength, int x, int y, BITMAP *sprite,
					BITMAP *p_sprite);
void createProjectile(Prosjektil *p, int antFrames, BITMAP *sprite);


void defDucks(Ducks *d,
				 // int maksvx, // for maksfart i x-retning?
				 // int maksvy, // for maksfart i y-retning?
				 int      maxleft,
				 int      maxright,
				 int	  x,
				 int	  y,
				 int      vx,
				 int      vy,
				 int      dir,
				 BITMAP   *sprite
				 );
#endif
