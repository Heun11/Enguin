#include<stdio.h>
#include"Enguin/Enguin.h"

#define W 80
#define H 40

int main()
{
	Enguin_Surface surf = Enguin_Surface_Init(W,H, ' ', 1, 1, (int[3]){163, 46, 106}, (int[3]){46, 149, 163});
	Enguin_Surface_Draw(&surf);
	
	int run = 1;
	const int fps = 60;
	const int frameDelay = 1000/fps;
	int frameStart, frameTime;
	char ch;
	char strFPS[64] = "FPS";

	float y = 0;
	float x = 0;


	while(run){
		ch = EnguinApi_Input_KeyPressed();
		if(ch=='q'||ch=='Q'||ch==KEY_ESC){
			break;
		}
		
		if(ch=='w'||ch=='W'){
			y-=1;
		}
		if(ch=='s'||ch=='S'){
			y+=1;
		}
		if(ch=='a'||ch=='A'){
			x-=2;
		}
		if(ch=='d'||ch=='D'){
			x+=2;
		}

		frameStart = EnguinApi_Utils_GetTicks();

		Enguin_Text_Draw(&surf, 20, H/2, "This is interactive demo of Enguin!", (int[3]){-1,-1,-1}, (int[3]){36, 35, 36});
		Enguin_Text_Draw(&surf, 20+1, H/2+1, "You are a small block in most top left corner,", (int[3]){-1,-1,-1}, (int[3]){36, 35, 36});
		Enguin_Text_Draw(&surf, 20+2, H/2+2, "Use AWSD to move out of it :)", (int[3]){-1,-1,-1}, (int[3]){36, 35, 36});

		Enguin_Rect_Draw(&surf, x, y, 2, 1, 'X', (int[3]){28, 27, 28}, (int[3]){217, 206, 217});

		Enguin_Text_Draw(&surf, 0, 0, strFPS, (int[3]){0,0,0}, (int[3]){245, 66, 164});
		Enguin_Surface_Update(&surf);

		frameTime = EnguinApi_Utils_GetTicks() - frameStart;
		if(frameDelay>frameTime){
			snprintf(strFPS, 7, "FPS:%d", (int)(1/(((float)frameDelay-(float)frameTime)/1000)));
			EnguinApi_Utils_Sleep((float)(frameDelay-frameTime));
		}
	}
	EnguinApi_Utils_Kill();
	return 0;
}
