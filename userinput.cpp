#include "userinput.h"

void fire(Towerman *towerman){
	if (towerman->shoots < towerman->maxShoots){
		int set = 1;
		for (int i=0; i<MAX_PROJECTILES && set == 1; i++){
			if (towerman->projectiles[i].onBoard == 0){
				setSpeed(&towerman->projectiles[i], towerman);
				set=0;
			}
		}
	}
}
