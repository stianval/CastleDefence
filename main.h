#ifndef _MAIN_H
#define _MAIN_H

#include "allegro.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef WIN32
#include "winalleg.h"
#include <Windows.h>
#else
#include <sys/time.h>
#include <time.h>
#endif

#define PI 3.14159265

#define MIN_INTERVAL  0.01
#define MAX_LATENCY   0.50

#define FRAME_DELAY 0.15

#define ANT_FLYVENDE 10
#define MAX_FLYING 7
#define MAX_PROJECTILES 5
#define DUCKS 5

#define GRAVITY 400

#include "structs.h"
#include "storage.h"
#include "drawing.h"
#include "physics.h"
#include "userinput.h"

void   initialize();
void   defineCreatures();
void   viewIntro();
void   gameLoop();
void   loadFiles();
double get_time();
void   game_tick(double dt);
void   draw_frame();
void   updateAll(double dt);
int    hitCreature(int nr); 
void   drawCreatures();
void   drawProjectiles();
void   drawExplotions();
void   putFlying();
BITMAP *load_tga_or_die(const char *path);
int    random(int min, int maks);
void   intToHex(char hex[11], int num);
void   outOfBoard(Flyvende *vesen);

//-------------------------------
// Axel branch
void draw_highscore();
void draw_credits();
void read_highscores();
void insert_highscore();
void write_highscore();
void game_over();
//-------------------------------

#endif
