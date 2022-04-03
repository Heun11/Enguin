#include<stdio.h>

#include"ash/ashTEngine.h"

int main()
{
	ASH_Surface surface = ASH_CreateSurface(50,50);
	int x = 0;

	while(1){
		ASH_DrawPoint(&surface,'@',x,5,50,166,168,1);
		++x;
		ASH_UpdateSurface(&surface);
		ASH_Delay(0.25f);
	}
	ASH_KillSurface(&surface);
	return 0;
}
