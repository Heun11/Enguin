 #include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	ENGUIN_Surface surface = ENGUIN_CreateSurface(40,40);
	float x = 0;

	while(1){
		ENGUIN_DrawPoint(&surface,' ',x+2, 5,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 5,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 5,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,5,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,5,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x+1, 6,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 6,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 6,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 6,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,6,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,6,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,6,79,79,79,0);

		ENGUIN_DrawPoint(&surface,' ',x+1, 7,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 7,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 7,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 7,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,7,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,7,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,7,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x+1, 8,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 8,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 8,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 8,237,175,17,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,8,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,8,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,8,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x, 9,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+1, 9,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 9,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 9,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 9,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,9,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,9,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,9,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+8,9,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x+1, 10,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 10,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 10,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 10,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,10,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,10,223,223,223,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,10,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x+2, 11,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 11,237,175,17,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 11,79,79,79,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,11,237,175,17,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,11,79,79,79,0);
		
		ENGUIN_DrawPoint(&surface,' ',x, 12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+1, 12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+2, 12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+3, 12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+4, 12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+5,12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+6,12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+7,12,128,215,232,0);
		ENGUIN_DrawPoint(&surface,' ',x+8,12,128,215,232,0);

		x+=0.1;

		ENGUIN_UpdateSurface(&surface);
		ENGUIN_Delay((float)1/30);
	}
	ENGUIN_KillSurface(&surface);
	return 0;
}
