#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	int WIDTH = 50, HEIGHT = 50;
	float x = 8;
	float y = 6;
	float dy = 0.2;
	float dx = 0.5;

	ENGUIN_Surface surface = ENGUIN_CreateSurface(WIDTH,HEIGHT, ' ', &((ENGUIN_Color){40,40,40}),&((ENGUIN_Color){102,186,157}));

	while(1){
		ENGUIN_DrawPoint(&surface,' ',(int)x,(int)y,&((ENGUIN_Color){240,120,228}),&((ENGUIN_Color){100,130,250}));
		x+=dx;
		y+=dy;

		if(x>WIDTH-1){
			dx = dx*(-1);
		}
		if(x<1){
			dx = dx*(-1);
		}

		if(y>HEIGHT-1){
			dy = dy*(-1);
		}
		if(y<1){
			dy = dy*(-1);
		}

		ENGUIN_UpdateSurface(&surface);
		ENGUIN_Delay((float)1/30);
	}
	ENGUIN_KillSurface(&surface);
	return 0;
}
