#include "main.h"

int has_sound = 1;

BITMAP *backbuffer;
BITMAP *background;
BITMAP *tower;
BITMAP *pisprite;
BITMAP *redwitch;
BITMAP *gernade;
BITMAP *ninja;
BITMAP *cross;
BITMAP *duck;
BITMAP *explosion;
BITMAP *colmap;
BITMAP *dragon;
BITMAP *vampire;
BITMAP *intro;
BITMAP *heart;
BITMAP *noducks;

SAMPLE *gameover  = NULL;

Flyvende flyingDef[ANT_FLYVENDE];
Flyvende flying[MAX_FLYING];

Towerman towerman;
Ducks    d[DUCKS];

BITMAP *b_font; 

double firetime = 0;
double timeUntilNext = 0;
int    flyingOnBoard = 0;

int score  = 0;
int ducksLeft  = DUCKS;
int bonus = 0;

//-----------------------------------------------------------------------------
int main(){
	initialize();
	viewIntro();
	gameLoop();
	return EXIT_SUCCESS;
}// main()
END_OF_MAIN();

//-----------------------------------------------------------------------------
// initialize() skal sette opp alt som trengs før selve spillet starter, sånn 
// som å initialisere globale variabler og å laste inn alle filer
void initialize(){
	int display_width  = 1024;
	int display_height = 768;

	allegro_init();
	install_timer();
	install_keyboard();

	if (-1 == install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0))
	{
		fprintf(stderr, "Disabling sound\n");
		has_sound = 0;
	}

        /* Request truecolor (RGBA) graphics */
	set_color_depth(32);

	if (-1 == set_gfx_mode(GFX_AUTODETECT, display_width, display_height, 0, 0))
	{
		fprintf(stderr, "Fatal error: Failed to set graphics mode %dx%d\n",
                        display_width, display_height);
		allegro_exit();
		exit(EXIT_FAILURE);
	}

	/* Create our canvas */
	backbuffer = create_bitmap(display_width, display_height);
	colmap     = create_bitmap(display_width, display_height);

	loadFiles();
	read_highscores();
	defineCreatures();
	createTowerman(&towerman, MAX_PROJECTILES, 3, 220, ((screen->w)-(ninja->w/3))/2, 400, ninja, gernade);

	set_alpha_blender();

	srand(time(NULL)); // gjør rand() ekte tilfeldig. Fungerer dette uten videre på linux?

	// sørger for at ingen starter på brettet
	for (int i=0; i<MAX_FLYING; i++) flying[i].life = -1;

	//putFlying(); // denne skal bort etter hvert
}

//-----------------------------------------------------------------------------
// defineCreatures skal initialisere de ulike vesnene
void defineCreatures(){
	// dette ser litt dumt ut, men det gjør det enklere å lage variasjoner hvis ønskelig
	defFlying(&flyingDef[0], 1, 2, 50, redwitch);
	defFlying(&flyingDef[1], 1, 2, 50, redwitch);
	defFlying(&flyingDef[2], 1, 2, 50, redwitch);
	defFlying(&flyingDef[3], 1, 2, 50, redwitch);
	defFlying(&flyingDef[4], 1, 2, 50, redwitch);
	defFlying(&flyingDef[5], 2, 2, 167, vampire);
	defFlying(&flyingDef[6], 2, 2, 167, vampire);
	defFlying(&flyingDef[7], 2, 2, 167, vampire);
	defFlying(&flyingDef[8], 3, 2, 311, dragon);
	defFlying(&flyingDef[9], 3, 2, 311, dragon);

	for (int i=0; i<DUCKS; i++){
		defDucks(&d[i], 10, 600, 500-30*i, 768-35, 35, 0, 1, duck);
	}	
}
//-----------------------------------------------------------------------------
void viewIntro(){
	blit(intro, screen, 0, 0, 0, 0, screen->w, screen->h);
	while(!key[KEY_SPACE]) {;}
	while(key[KEY_SPACE]) {;} 
}

//-----------------------------------------------------------------------------
// gameLoop() er hovedløkka i spillet
void gameLoop(){
	double start_time;
	double current_time;
	double target_time;
	double last_game_time = 0.0;

	start_time = get_time();

	while (!key[KEY_ESC] && ducksLeft > 0)
	{
		current_time = get_time();
		target_time = current_time - start_time;

		/* If the computer's clock has been adjusted backwards,
		 * compensate */
		if (target_time < last_game_time)
			start_time = current_time - last_game_time;

		/* If the game time lags too much, for example if the computer
		 * has been suspended, avoid trying to catch up */
		if (target_time > last_game_time + MAX_LATENCY)
			last_game_time = target_time - MAX_LATENCY;

		/* If more than MIN_INTERVAL has passed since last update, run
		 * game_tick() again. */
		if (target_time > last_game_time + MIN_INTERVAL)
		{
			game_tick(target_time - last_game_time);
			last_game_time = target_time;
		}

		/* Clear the canvas */
		clear(backbuffer);

		draw_frame();

		/* We are done drawing on the canvas -- show it to the user */
		blit(backbuffer, screen, 0, 0, 0, 0, screen->w, screen->h);
	}
	game_over();
	insert_highscore();
	draw_highscore();
	write_highscore();
	//draw_credits();
}// gameLoop()

//-----------------------------------------------------------------------------
// loadFiles() skal laste inn alle filer
void loadFiles(){
	
	b_font     = load_tga_or_die("art/lazyfont.tga");
	tower      = load_tga_or_die("art/Castle_only.tga");
	background = load_tga_or_die("art/background_nocastle.tga");
	pisprite   = load_tga_or_die("art/pi_test.tga");
	redwitch   = load_tga_or_die("art/witch_anim.tga");
	gernade    = load_tga_or_die("art/bomb.tga");
	ninja      = load_tga_or_die("art/topninja_anim.tga");
	//background = load_tga_or_die("art/Castle_background.tga");
	cross      = load_tga_or_die("art/cross.tga");
	duck       = load_tga_or_die("art/Duck.tga");
	explosion  = load_tga_or_die("art/Boom.tga");
	dragon     = load_tga_or_die("art/Dragon_anim.tga");
	vampire    = load_tga_or_die("art/Vampire_anim.tga");
	intro      = load_tga_or_die("art/Intro.tga");
	heart      = load_tga_or_die("art/Heart_Life.tga");
	noducks    = load_tga_or_die("art/gameover.tga");


	//ALL THE SOUNDS :P :):)
	gameover   = load_wav("art/Heksehyl22.wav");
}

//-----------------------------------------------------------------------------
double get_time()
{
#ifndef WIN32
	struct timeval tv;

	gettimeofday(&tv, 0);

	return tv.tv_sec + tv.tv_usec * 1.0e-6;
#else
	return GetTickCount() / 1000.0;
#endif
}
//-----------------------------------------------------------------------------
// game_tick() oppdaterer alle forandringer
void game_tick(double dt){
	// reduserer firetime
 	if (firetime > 0) firetime -= dt;
	if (firetime < 0) firetime = 0;

	// hent input fra brukeren
	if (key[KEY_LEFT]){
		if (towerman.aimAngle < 180) towerman.aimAngle += 150*dt;
		if (towerman.aimAngle > 180) towerman.aimAngle = 180;
	}
	if (key[KEY_RIGHT]){
		if (towerman.aimAngle > 0) towerman.aimAngle -= 150*dt;
		if (towerman.aimAngle < 0) towerman.aimAngle = 0;
	}
	if (key[KEY_SPACE] && firetime == 0){
		fire(&towerman);
		firetime = 0.15;
	}

	updateAll(dt);
}

//-----------------------------------------------------------------------------
// draw_frame() skal tegne oppdatert bilde 
void draw_frame(){
	blit (background, backbuffer, 0, 0, 0, 0, screen->w, screen->h); 

	draw_cross(&towerman, cross, backbuffer);

	drawProjectiles();
	draw_t(&towerman, backbuffer);
	
	draw_trans_sprite(backbuffer, tower, ((screen->w)-(tower->w))/2, screen->h - 82 - tower->h);

	drawCreatures();
	
	drawExplotions();

	for (int i=0; i<ducksLeft; i++){
		draw_ducks(duck, backbuffer, &d[i]);
	}

	char t_score[18];
	strcpy(t_score, "Score: ");
	intToHex(&t_score[7], score);
	draw_text(b_font, backbuffer, 12, 12, 1, 6, t_score);

	for (int i=0; i<bonus; i++){
		draw_trans_sprite(backbuffer, heart, screen->w - heart->w * (i+1) - 8, 12);
	}
}

//-----------------------------------------------------------------------------
// updateAll() skal oppdatere bevegelsen til vesnene
void updateAll(double dt){
	timeUntilNext -= dt;
	if (timeUntilNext < 0 || flyingOnBoard == 0) putFlying();

	clear_to_color(colmap, makecol(255, 255, 255));
	for (int i=0; i<MAX_FLYING; i++){
		if (updateCreature(dt, &flying[i])) putOnCol(&flying[i], i, colmap);
	}
	updateProjectiles(dt, &towerman, colmap);
	updateTowerman(dt, &towerman);
	for (int i=0; i<ducksLeft; i++){ 
		updateDucks(dt, &d[i]);
	}
}
//-----------------------------------------------------------------------------
int hitCreature(int nr){
	if (nr != -1){
		Flyvende *vesen = &flying[nr];
		vesen->life--;
		if (vesen->life == 0){
			score += vesen->score;
			flyingOnBoard--;
			vesen->animtime = 0.07;
		}
		if (vesen->life < 0){
			towerman.strength += -10*vesen->life;
			bonus += -vesen->life;
			if (bonus > 15) bonus = 15;
		}
	}
	return 1;
}

//-----------------------------------------------------------------------------
// drawCreatures() skal tegne vesnene på brettet
void drawCreatures(){
	for (int i = 0; i < MAX_FLYING; i++){
		Flyvende *vesen = &flying[i];
		if (vesen->life > -1){
			draw(vesen, backbuffer);
		}
	}
}// drawCreatures()
//-----------------------------------------------------------------------------
// drawProjectiles() skal tegne prosjektilene som er i lufta
void drawProjectiles(){
	for (int i=0; i<towerman.maxShoots; i++){
		Prosjektil *p = &towerman.projectiles[i];
		if (p->onBoard == 1){
			draw_p(p, backbuffer);
		}
	}
}
//-----------------------------------------------------------------------------
void drawExplotions(){
	for (int i=0; i<towerman.maxShoots; i++){
		Prosjektil *p = &towerman.projectiles[i];
		if (p->onBoard == 2){
			draw_exp(p, explosion, backbuffer);
		}
	}
}
//-----------------------------------------------------------------------------
// putFlying() skal putte et vesen på brettet
void putFlying(){
	timeUntilNext = 0;
	for (int i=0; i<MAX_FLYING && timeUntilNext == 0; i++){
		Flyvende *vesen = &flying[i];
		if (vesen->life == -1){
			flyingOnBoard++;
			timeUntilNext = flyingOnBoard*flyingOnBoard*random(0, 100000/(score+1))/100.0;
			int type = random(0, ANT_FLYVENDE-1);
 			flying[i] = flyingDef[type];

			int w = vesen->sprite->w;

			int ypos = random(0, 300);
			int vx   = random(50+10*(10-type), 50+10*(10-type) + score/500);
			int vy_min = -vx*ypos/(screen->h + w);
			int vy_max = vx*(300-ypos)/(screen->h + w);

			int xpos = random(0, 1);
			if (xpos == 0) xpos =  -w + 1;
			else{
				xpos = screen->w - 1;
				vx   = -vx;
			}
			
			int vy = random(vy_min, vy_max);

			posFlying(vesen, xpos, ypos, vx, vy, type);
		}
	}

	/*
	// Legger en rød heks på brettet. Dette skal skiftes ut med noe mer generelt
	flying[0] = flyingDef[0];
	// XXX Mangler det ikke 1 argument på slutten her?
	posFlying(&flying[0], 0, 25, 50);

	// Legger en vampyr på brettet
	flying[1] = flyingDef[1];
	posFlying(&flying[1], screen->w, 50, -250, 70);

	flying[2] = flyingDef[2];
	posFlying(&flying[2], 0, 300, 500, -100);
	*/
} // putFlying()
//-----------------------------------------------------------------------------
// Laster inn bilde eller avbryter programmet med en feilmelding
BITMAP *load_tga_or_die(const char *path)
{
	BITMAP *result;
	result = load_tga(path, 0);
	if (!result)
	{
		fprintf(stderr, "Failed to load image '%s'\n", path);
		exit(EXIT_FAILURE);
	}
	return result;
}

//-----------------------------------------------------------------------------
// random() skal returnere et tilfeldig heltall mellom min og maks
int random(int min, int maks){
	int tall = rand() % (maks - min + 1);
	return tall + min;
}
//-----------------------------------------------------------------------------

void intToHex(char hex[11], int num){
	int siffer;
	hex[0]  = '0';
	hex[1]  = 'x';
	hex[10] = '\0';
	for (int i=9; i>=2; i--){
		siffer = num % 16;
		num /= 16;
		if (siffer < 10) hex[i] = '0' + (char) siffer;
		else hex[i] = 'A' + (char) siffer - (char) 10;
	}
}

//-----------------------------------------------------------------------------

void   outOfBoard(Flyvende *vesen){
	if (vesen->life > 0){
		ducksLeft--;
		flyingOnBoard--;
	}
	vesen->life = -1;
}

//-----------------------------------------------------------------------------
// Axel branch

int highscore[10] = {9,8,7,6,5,4,3,2,1,0};


void insert_highscore(){
	for (int i=9; i>=0; i--){
		if (score > highscore[i]){
			if (i<9) highscore[i+1] = highscore[i];
			highscore[i] = score;
		}
	}	
}

void read_highscores(){
	
	FILE * pFile;
	int i=0;
	char buffer [100];

	pFile = fopen ("highscores.txt" , "r");
	if (pFile == NULL) perror ("Error opening file");
	else
	{
		while ( (i < 10) || !feof(pFile) )
		{
			fgets (buffer , 100 , pFile);
			highscore[i] = atoi(buffer);
			i++;
			
		}
		fclose (pFile);
	}
}

void draw_highscore(){
	char score_text[11];
	int  vist = 0;
	clear(backbuffer);
	clear_to_color(backbuffer, makecol(255, 255, 255));
	draw_text(b_font, backbuffer, 250, 130, 1, 6,"Highscores:");	
	for (int i = 0; i< 10; i++){
		intToHex(score_text, highscore[i]);
		draw_text(b_font, backbuffer, 300, 130+45+(i*45), 1, 6,score_text);
		if (score == highscore[i] && !vist){
			draw_text(b_font, backbuffer, 100, 130+45+(i*45), 1, 6,"---->");
			draw_text(b_font, backbuffer, 575, 130+45+(i*45), 1, 6,"<----");
			vist = 1;
		}
	}
	draw_text(b_font, backbuffer, 300, 130+45+450+50, 1, 6,"[Press Space]");
	blit(backbuffer, screen, 0, 0, 0, 0, screen->w, screen->h);
	while (!key[KEY_SPACE])continue;
	key[KEY_SPACE] = 0;
}

void draw_credits(){
	while (!key[KEY_SPACE])

	{
		clear(backbuffer);

//		draw_text(b_font, backbuffer, 12, 12, 1, 6,"Highscore:");	
	}
}

void write_highscore(){
	FILE *pFile;
	int i = 0;
	char *filename = "highscores.txt";
	pFile = fopen (filename , "w");

	if (pFile == NULL) perror ("Error opening file");
	else
	{
		while (i<10 )
		{
			fprintf(pFile, "%d\n", highscore[i++]);
		}
		fclose (pFile);
	}
}

void game_over(){
	draw_trans_sprite(backbuffer, noducks, 0, 0);
	blit (backbuffer, screen, 0, 0, 0, 0, screen->w, screen->h);
	if (has_sound && gameover != NULL) play_sample(gameover, 255, 255/2, 1000, 0 );

	while (key[KEY_SPACE]) {;}
	while (!key[KEY_SPACE]) {;}
	while (key[KEY_SPACE]) {;}

}
