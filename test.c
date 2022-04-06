#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	int WIDTH = 100, HEIGHT = 100;
	ENGUIN_Surface surface = ENGUIN_CreateSurface(WIDTH,HEIGHT);
	float x = 8;
	float y = 6;
	float dy = 1.2;
	float dx = 1.5;

	while(1){
		ENGUIN_DrawPoint(&surface,' ',(int)x,(int)y,50,166,168,0);
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
		ENGUIN_Delay((float)1/60);
	}
	ENGUIN_KillSurface(&surface);
	return 0;
}
