#include"surface.h"

// Surface
Enguin_Surface Enguin_Surface_Init(int width, int height, char ch, int wantF, int wantB, int fore[3], int back[3])
{
	signal(SIGINT, EnguinApi_Utils_Kill);
	EnguinApi_Canvas_CursorHide();
	EnguinApi_Canvas_InputHide();
	Enguin_Surface surface = {.width=width, .height=height, .default_char=ch};
	for(int i=0;i<3;i++){
		surface.default_back[i] = back[i];
		surface.default_fore[i] = fore[i];
	}
	surface.canvas = EnguinApi_Canvas_Create(width, height, wantF, wantB, back, fore, ch);
	return surface;
}

void Enguin_Surface_Draw(Enguin_Surface* surface)
{
	printf("\e[8;%d;%dt", surface->height, surface->width);
	EnguinApi_Canvas_Flush(&surface->canvas);
}

void Enguin_Surface_Update(Enguin_Surface* surface)
{
	EnguinApi_Canvas_Flush(&surface->canvas);
	EnguinApi_Canvas_Erease(&surface->canvas, 0, 0, surface->width-1, surface->height-1);
}

// Text
void Enguin_Text_Draw(Enguin_Surface* surface, int x, int y, char* text, int fore[3], int back[3])
{
	EnguinApi_Canvas_MoveTo(&surface->canvas, x, y);
	EnguinApi_Canvas_Erease(&surface->canvas, x, y, x+strlen(text)-1, y);
	EnguinApi_Canvas_Write(&surface->canvas, text, fore, back);
}

// Graphics
void Enguin_Pixel_Draw(Enguin_Surface* surface, int x, int y, char pixel, int fore[3], int back[3])
{
	EnguinApi_Canvas_MoveTo(&surface->canvas, x, y);
	EnguinApi_Canvas_EreaseOne(&surface->canvas, x, y);
	char buff[4];
	sprintf(buff, "%c", pixel);
	EnguinApi_Canvas_Write(&surface->canvas, buff, fore, back);
}

void Enguin_Rect_Draw(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3])
{
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			Enguin_Pixel_Draw(surface, x+i, y+j, pixel, fore, back);
		}	
	}
}