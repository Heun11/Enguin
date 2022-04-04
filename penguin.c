 #include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	ENGUIN_Surface surface = ENGUIN_CreateSurface(40,40);
	
	//ASH_DrawPoint(&surface,'@',5,5,50,166,168,1);
	
	ENGUIN_DrawPoint(&surface,' ',7, 5,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',8, 5,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',9, 5,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',10,5,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',11,5,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',6, 6,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',7, 6,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',8, 6,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',9, 6,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',10,6,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',11,6,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',12,6,79,79,79,0);

	ENGUIN_DrawPoint(&surface,' ',6, 7,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',7, 7,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',8, 7,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',9, 7,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',10,7,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',11,7,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',12,7,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',6, 8,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',7, 8,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',8, 8,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',9, 8,237,175,17,0);
	ENGUIN_DrawPoint(&surface,' ',10,8,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',11,8,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',12,8,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',5, 9,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',6, 9,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',7, 9,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',8, 9,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',9, 9,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',10,9,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',11,9,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',12,9,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',13,9,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',6, 10,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',7, 10,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',8, 10,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',9, 10,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',10,10,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',11,10,223,223,223,0);
	ENGUIN_DrawPoint(&surface,' ',12,10,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',7, 11,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',8, 11,237,175,17,0);
	ENGUIN_DrawPoint(&surface,' ',9, 11,79,79,79,0);
	ENGUIN_DrawPoint(&surface,' ',10,11,237,175,17,0);
	ENGUIN_DrawPoint(&surface,' ',11,11,79,79,79,0);
	
	ENGUIN_DrawPoint(&surface,' ',5, 12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',6, 12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',7, 12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',8, 12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',9, 12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',10,12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',11,12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',12,12,128,215,232,0);
	ENGUIN_DrawPoint(&surface,' ',13,12,128,215,232,0);

	ENGUIN_UpdateSurface(&surface);
	ENGUIN_KillSurface(&surface);
	return 0;
}
