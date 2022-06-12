#include"surface.h"

Enguin_Surface Enguin_Surface_Init(int width, int height, char ch, int front[3], int back[3])
{
	EnguinApi_Canvas_CursorHide();
	EnguinApi_Canvas_InputHide();
	Enguin_Surface surface = {.width=width, .height=height, .default_char=ch};
	for(int i=0;i<3;i++){
		surface.default_back[i] = back[i];
		surface.default_front[i] = front[i];
	}
	surface.canvas = EnguinApi_Canvas_Create(width, height);
	surface.cells = (EnguinApi_Cell*)malloc(width*height*sizeof(EnguinApi_Cell));
	for(int i=0;i<width*height;i++){
		surface.cells[i] = EnguinApi_Cell_Create(ch, i%width, i/width, front, back);
	}
	return surface;
}

