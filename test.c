#include<stdio.h>

#include"Enguin/Enguin.h"

int main()
{
	int WIDTH = 50, HEIGHT = 50;
	int x = 0;
	int y = 0;

	ENGUIN_Surface surface = ENGUIN_CreateSurface(WIDTH,HEIGHT, ' ', &((ENGUIN_Color){40,40,40}),&((ENGUIN_Color){102,186,157}));

	char c;

	while(1){
		if(ENGUIN_Kbhit()){
			c = ENGUIN_Getch();
			if(c=='q'){
				break;
				ENGUIN_KillSurface(&surface);
			}
			else if(c=='w'){
				y-=1;
			}
			else if(c=='s'){
				y+=1;
			}
			else if(c=='a'){
				x-=1;
			}
			else if(c=='d'){
				x+=1;
			}
		}

		ENGUIN_DrawPoint(&surface,' ',x,y,&((ENGUIN_Color){240,120,228}),&((ENGUIN_Color){100,130,250}));

		ENGUIN_UpdateSurface(&surface);
		ENGUIN_Delay((float)1/60);
	}
	ENGUIN_KillSurface(&surface);
	return 0;
}
