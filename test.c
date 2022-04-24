// #include<stdio.h>

// #include"Enguin/Enguin.h"

// int main()
// {
// 	int WIDTH = 50, HEIGHT = 50;
// 	int x = 0;
// 	int y = 0;

// 	ENGUIN_Surface surface = ENGUIN_CreateSurface(WIDTH,HEIGHT, ' ', &((ENGUIN_Color){40,40,40}),&((ENGUIN_Color){102,186,157}));

// 	char c;

// 	int run = 1;
// 	while(run){

// 		if(ENGUIN_Kbhit()){
// 			c = ENGUIN_Getch();
// 			if(c=='q'||c=='Q'){
// 				run = 0;
// 			}
// 			else if(c=='w'||c=='W'){
// 				y-=1;
// 			}
// 			else if(c=='s'||c=='S'){
// 				y+=1;
// 			}
// 			else if(c=='a'||c=='A'){
// 				x-=1;
// 			}
// 			else if(c=='d'||c=='D'){
// 				x+=1;
// 			}
// 		}

// 		ENGUIN_DrawPoint(&surface,' ',x,y,&((ENGUIN_Color){240,120,228}),NULL);

// 		ENGUIN_UpdateSurface(&surface);
// 		ENGUIN_Delay(1/10);
// 	}
// 	ENGUIN_KillSurface(&surface);
// 	return 0;
// }

#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	ENGUIN_Surface s = ENGUIN_CreateSurface(30,30);
	ENGUIN_DrawSurface(&s);

	int x = 0;

	int run = 1;
	while(run){
		ENGUIN_DrawPoint(&s, x,29,'X');
		x++;

		ENGUIN_UpdateSurface(&s);
		
		ENGUIN_Delay(1);
	}
	ENGUIN_KillSurface(&s);
	
	return 0;
}
