// #include<stdio.h>

// #include"Enguin/Enguin.h"

// int main()
// {
// 	ENGUIN_Surface s = ENGUIN_CreateSurface(30,30);
// 	ENGUIN_DrawSurface(&s);

// 	float x = 2;

// 	int run = 1;
// 	while(run){
// 		// ENGUIN_DrawPoint(&s, (int)x,2,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,4,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,6,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,8,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,10,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,12,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,14,'X');
// 		// ENGUIN_DrawPoint(&s, (int)x,16,'X');

// 		// if(x<26){
// 		// 	x+=0.0001;
// 		// }

// 		ENGUIN_CursorMoveTo(&s, x, 2);
// 		ENGUIN_CursorWrite(&s, 'C');
		
// 		if(x<26){
// 			x+=0.0001;
// 		}

// 		ENGUIN_UpdateSurface(&s);
		
// 		ENGUIN_Delay(1/30);
// 	}
// 	ENGUIN_KillSurface(&s);
	
// 	return 0;
// }

#include<stdio.h>
#include"Enguin/Enguin.h"

int main()
{
	Enguin_Surface surf = Enguin_Surface_Init(30,30, ' ',(int[3]){128,210,143},(int[3]){-1,-1,-1});
	return 0;
}
