#include"surface.h"

Enguin_Surface Enguin_Surface_Init(int width, int height, char ch, int front[3], int back[3])
{
	signal(SIGINT, EnguinApi_Utils_Kill);
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
		//surface.canvas.cells[i] = EnguinApi_Cell_Create(ch, i%width, i/width, front, back);
	}
	return surface;
}

void Enguin_Surface_Draw(Enguin_Surface* surface)
{
	EnguinApi_Canvas_Flush(&surface->canvas);
}

void Enguin_Surface_Update(Enguin_Surface* surface)
{
	for(int i=0;i<surface->width*surface->height;i++){
		EnguinApi_Canvas_MoveTo(&surface->canvas, i%surface->width, i/surface->width);
		char char_str[4];
		snprintf(char_str, 4, "%c", surface->cells[i].ch);
		EnguinApi_Canvas_Write(&surface->canvas, char_str);

		EnguinApi_Cell_Reset(&surface->cells[i]);
	}
	EnguinApi_Canvas_Flush(&surface->canvas);
}
