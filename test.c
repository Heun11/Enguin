#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	ASH_Surface surface = ASH_CreateSurface(50,50);
	float x = 0;

	while(1){
		ASH_DrawPoint(&surface,'@',(int)x,5,50,166,168,1);
		x+=0.2;
		ASH_UpdateSurface(&surface);
		ASH_Delay((float)1/30);
	}
	ASH_KillSurface(&surface);
	return 0;
}
