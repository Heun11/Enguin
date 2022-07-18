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

//TODO -> write test -> 
//	-> this up 
//	-> Fake dino

int main()
{
	Enguin_Surface surf = Enguin_Surface_Init(30,30, '.',(int[3]){-1,-1,-1},(int[3]){-1,-1,-1});
	Enguin_Surface_Draw(&surf);
	char key;

	float x = 2;

	while(1){
		key = EnguinApi_Input_KeyPressed();
		if(key==KEY_ESC || key=='q' || key=='Q'){
			break;
		}

		//for(int i=0;i<30*30;i++){
		//	surf.cells[i].ch = EnguinApi_Utils_RandomNumber(65, 125);
		//}

		if(x<26){
			x+=1;
		}

		surf.cells[1*30+(int)x].ch = 'X';
		surf.cells[3*30+(int)x].ch = 'X';
		surf.cells[5*30+(int)x].ch = 'X';
		surf.cells[7*30+(int)x].ch = 'X';

		Enguin_Surface_Update(&surf);
		EnguinApi_Utils_Sleep((float)1/120);
	}

	EnguinApi_Canvas_InputShow();
	EnguinApi_Canvas_CursorShow();
	return 0;
}
