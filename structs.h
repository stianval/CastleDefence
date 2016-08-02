#ifndef _STRUKTURER_H
#define _STRUKTURER_H

#include "main.h"

struct Prosjektil{
	int    onBoard; // Forteller om det aktuelle prosjektilet er på brettet
	double x;
	double y;
	double vx;
	double vy;
	double angle;
	double animtime;
	int    frame;
	int    antFrames;
	BITMAP *sprite;
};

struct Flyvende{
	int    type;
	double x;
	double y;
	double vx; // fart i x-retning
	double vy; // fart i y-retning
	double animtime;
	int    life; // hvis life==0 er vesenet borte, mens hvis life<0 er vesenet i fall?
	int    frame;
	int    antFrames;
	int    score;
	BITMAP *sprite;
};

struct Towerman{
	int    x;  // ?
	int	   y;  // ?
	double aimAngle;
	int    strength;
	int    shoots;
	int    maxShoots; // antall prosjektiler han kan skyte samtidig 
	int    frame;
	int    antFrames;
	double animtime;
	BITMAP *sprite;
	Prosjektil projectiles[MAX_PROJECTILES];
};

struct Ducks{
	double x;
	int    y;
	double vx;
	double vy;
	int  maxleft;
	int  maxright;
	int  dir;
	BITMAP *sprite;
};

#endif
