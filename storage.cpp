#include "storage.h"

//------------------------------------------------------------------------------------------------------
// defFlying() er en funksjon for å definere de ulike vesnene
void defFlying(Flyvende *vesen,
				 // int maksvx, // for maksfart i x-retning?
				 // int maksvy, // for maksfart i y-retning?
				 int      life,
				 int      antFrames,
				 int      score, 
				 BITMAP *sprite)
{
	vesen->life        = life;
	vesen->antFrames   = antFrames;
	vesen->score       = score;
	vesen->sprite      = sprite;
	vesen->animtime    = 0;
	vesen->vx          = 0;
	vesen->vy          = 0;  
	vesen->x           = 0;  
	vesen->y           = 0;  
}

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
				 )
{
	d->maxleft         = maxleft;
	d->maxright	       = maxright;
	d->x               = x;
	d->y               = y;
	d->vx              = vx;
	d->vy              = vy;
	d->dir             = dir;
	d->sprite          = sprite;
}

//------------------------------------------------------------------------------------------------------
// posFlying() skal plassere et flyvende vesen og gi den fart
void posFlying(Flyvende *vesen, int x, int y, int vx, int vy, int type){
	vesen->x  = x;
	vesen->y  = y;
	vesen->vx = vx;
	vesen->vy = vy;
	vesen->type = type;
}

//------------------------------------------------------------------------------------------------------

void createTowerman(Towerman *t, int maxShoots, int frames, int strength, int x, int y, BITMAP *sprite,
					BITMAP *p_sprite){
	t->maxShoots = maxShoots;
	t->antFrames = frames;
	t->sprite    = sprite;
	t->shoots    = 0;
	t->frame     = 0;
	t->strength  = strength;
	t->x         = x;
	t->y         = y;
	t->aimAngle  = 45;
	t->animtime  = 0;
	for (int i=0; i<MAX_PROJECTILES; i++){
		createProjectile(&t->projectiles[i], 1, p_sprite);
	}
}

//------------------------------------------------------------------------------------------------------

void createProjectile(Prosjektil *p, int antFrames, BITMAP *sprite){
	p->sprite    = sprite;
	p->onBoard   = 0;
	p->frame     = 0;
	p->antFrames = antFrames;
	p->animtime  = 0;
	p->angle     = 0;
}
