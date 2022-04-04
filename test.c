#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	ENGUIN_Surface surface = ENGUIN_CreateSurface(50,50);
	float x = 0;

	while(1){
		ENGUIN_DrawPoint(&surface,'@',(int)x,5,50,166,168,1);
		x+=0.2;
		ENGUIN_UpdateSurface(&surface);
		ENGUIN_Delay((float)1/30);
	}
	ENGUIN_KillSurface(&surface);
	return 0;
}
