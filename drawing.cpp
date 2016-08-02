#include "drawing.h"

//------------------------------------------------------------------------------------------------------
// draw() er en funksjon for å tegne flyvende vesen på brettet. Sprite må være tegnet mot høyre.
void draw(Flyvende *vesen, BITMAP *backbuffer){

	// Forutsetter at alle framene er like brede og lagt i bredden på samme bilde
	int framewidth = vesen->sprite->w / vesen->antFrames; 
	int heigth     = vesen->sprite->h;

	// Lager to hjelpebitmaps
	BITMAP *source   = create_bitmap(framewidth, heigth); // Skal inneholde riktig frame
	BITMAP *sprite_f = create_bitmap(framewidth, heigth); // Skal inneholde flippet bilde om nødvendig

	blit(vesen->sprite, source, framewidth * vesen->frame, 0, 0, 0, framewidth, heigth);	

	// Tegner sprite på backbuffer
	if (vesen->vx < 0){
		draw_sprite_h_flip(sprite_f, source, 0, 0);
		draw_trans_sprite(backbuffer, sprite_f, (int)vesen->x, (int)vesen->y);
	}
	else {
		draw_trans_sprite(backbuffer, source, (int)vesen->x, (int)vesen->y);
	}
	destroy_bitmap(source);
	destroy_bitmap(sprite_f);
}

//------------------------------------------------------------------------------------------------------
// draw_p() tegner et prosjektil
void draw_p(Prosjektil *p, BITMAP *backbuffer){
	draw_trans_sprite(backbuffer, p->sprite, (int) p->x, (int) p->y);	
}
			
void draw_exp(Prosjektil *p, BITMAP *exp, BITMAP *backbuffer){
	draw_trans_sprite(backbuffer, exp, (int) p->x - exp->w/2, (int) p->y - exp->h/2);
}

void draw_ducks(BITMAP *duck, BITMAP *backbuffer, Ducks *d){
	
	int framewidth = d->sprite->w; 
	int heigth = d->sprite->h;
	
	BITMAP *source   = create_bitmap(framewidth, heigth); // Skal inneholde riktig frame
	BITMAP *sprite_f = create_bitmap(framewidth, heigth); // Skal inneholde flippet bilde om nødvendig
	
	blit(duck, source, 0, 0, 0, 0, framewidth, heigth);
	
	if (d->dir == 2){
		draw_sprite_h_flip(sprite_f, source,0 ,0 );
		draw_trans_sprite(backbuffer, sprite_f, (int) d->x, d->y);
	}
	else {
		draw_trans_sprite(backbuffer, duck, (int) d->x, d->y);
	}
	destroy_bitmap(source);
	destroy_bitmap(sprite_f);
}

// draw_text tegner text på skjermen
void draw_text(BITMAP *source, BITMAP *backbuffer, int x, int y, int x_frame,int y_frame,char *text)
{
	int spriteW = 39;
	int spriteH = 55;	       

	BITMAP *output = create_bitmap(spriteW, spriteH);

	for (unsigned int i=0; i<strlen(text); i++){
		int x_col, y_col;
		y_col = text[i]/16; x_col = text[i]%16;
		//printf("%c %d %d\n ",text[i],x_col,y_col);
		masked_blit(source, output, x_col * spriteW, y_col * spriteH, 0, 0, spriteW, spriteH); //Copy right frame from source
		draw_trans_sprite(backbuffer, output, x+(i*16), y);
	}

	destroy_bitmap(output);
}

void draw_t(Towerman *vesen, BITMAP *backbuffer){

	// Forutsetter at alle framene er like brede og lagt i bredden på samme bilde
	int framewidth = vesen->sprite->w / vesen->antFrames; 
	int heigth = vesen->sprite->h;

	// Lager to hjelpebitmaps
	BITMAP *source   = create_bitmap(framewidth, heigth); // Skal inneholde riktig frame
	BITMAP *sprite_f = create_bitmap(framewidth, heigth); // Skal inneholde flippet bilde om nødvendig

	blit(vesen->sprite, source, framewidth * vesen->frame, 0, 0, 0, framewidth, heigth);	

	// Tegner sprite på backbuffer
	if (vesen->aimAngle > 90){
		draw_sprite_h_flip(sprite_f, source, 0, 0);
		draw_trans_sprite(backbuffer, sprite_f, (int)vesen->x, (int)vesen->y);
	}
	else {
		draw_trans_sprite(backbuffer, source, (int)vesen->x, (int)vesen->y);
	}
	destroy_bitmap(source);
	destroy_bitmap(sprite_f);
}

void draw_cross(Towerman *t, BITMAP *cross, BITMAP *backbuffer){
	int x0 = t->x + (t->sprite->w / (2 * t->antFrames)) - cross->w/2;
	int y0 = t->y + (t->sprite->h / 2) - cross->h/2;
	int x  = x0 + 100 * cos(PI*t->aimAngle/180);
	int y  = y0 - 100 * sin(PI*t->aimAngle/180);
	draw_trans_sprite(backbuffer, cross, x, y);
}
