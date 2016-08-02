#include "physics.h"

int updateCreature(double dt, Flyvende *vesen){
	if (vesen->life >= 0){

		vesen->x += vesen->vx * dt;
		vesen->y += vesen->vy * dt;		

		if (!fly_offBoard(vesen)){	
			if (vesen->life == 0){
				vesen->vy += GRAVITY * dt;
				vesen->frame = 0;
				vesen->animtime -= dt;
				if (vesen->animtime <= 0){
					vesen->animtime = 0;
					return 0;
				}	
				return 1;
			}
			else{
				vesen->animtime += dt;
				if (vesen->animtime > FRAME_DELAY){
					vesen->animtime -= FRAME_DELAY;
					vesen->frame++;
					vesen->frame %= vesen->antFrames;
				}
				return 1;
			}
		}
	}
	return 0;
}

void setSpeed(Prosjektil *p, Towerman *t){
 	p->onBoard = 1;
	p->vx = cos(t->aimAngle*PI/180) * t->strength;
	p->vy = -sin(t->aimAngle*PI/180) * t->strength;
	p->x  = t->x + t->sprite->w/(3*2) - p->sprite->w/2;
	p->y  = t->y + t->sprite->h/2 - p->sprite->h/2;
}

/*
int pro_offBoard(Prosjektil *p, Towerman *t){
	int xLeft   = p->x;
	int xRight  = xLeft + p->sprite->w;
	int yTop    = p->y;
	int yButtom = yTop + p->sprite->h;

	if (xLeft > screen->w || xRight < 0|| yButtom < 0){
		p->onBoard = 0;
		t->shoots--;
		return 1;
	}
	return 0;
}
*/

int fly_offBoard(Flyvende *vesen){
	int xLeft   = vesen->x;
	int xRight  = xLeft + vesen->sprite->w;
	int yTop    = vesen->y;
	int yButtom = yTop + vesen->sprite->h;

	if (xLeft > screen->w || xRight < 0 || yButtom < 0 || yTop > screen->h){
		outOfBoard(vesen);
		return 1;
	}
	return 0;
}

void updateProjectiles(double dt, Towerman *t, BITMAP *colmap){
	for (int i=0; i<t->maxShoots; i++){
		Prosjektil *p = &t->projectiles[i];

		if (p->onBoard == 2){ // dette tilsvarer eksplosjon
			p->animtime -= dt;
			if (p->animtime < 0){
				p->onBoard = 0;
				t->shoots--;
			}
		}

		if (p->onBoard == 1){
			p->x += p->vx * dt;
			p->y += p->vy * dt;

			p->angle += 180 * dt;

			int xpos = (int) p->x + p->sprite->w/2;
			int ypos = (int) p->y + p->sprite->h/2;

			int color = getpixel(colmap, (int) p->x, (int) p->y);
			if (color != makecol(255, 255, 255)){
				if(hitCreature(color)){
					p->onBoard = 2;
					p->animtime = 0.1;
				}
			}
		}
	}
}

void updateTowerman(double dt, Towerman *t){
	t->animtime += dt;
	if (t->animtime > FRAME_DELAY){
		t->animtime -= FRAME_DELAY;
		t->frame++;
		t->frame %= t->antFrames;
	}
}

void updateDucks(double dt, Ducks *d){
	if (d->dir == 2) {
		if (d->x > d->maxright) d->dir = 1;
		d->x += d->vx * dt;
	}else if (d->dir == 1){
		if (d->x < d->maxleft) d->dir = 2;
		d->x -= d->vx * dt;
	}
}

void putOnCol(Flyvende *vesen, int nr, BITMAP *colmap){
	double w = vesen->sprite->w/(2*vesen->antFrames);
	double h = vesen->sprite->h/2;
	int xpos = vesen->x + w;
	int ypos = vesen->y + h;
	double radius = sqrt(w*w + h*h);
	circlefill(colmap, xpos, ypos, radius, nr);
}
