#ifndef ENGUIN
#define ENGUIN
#pragma once

#include"../enguin_api/enguinApi.h"

typedef struct{
	EnguinApi_Canvas canvas;
	EnguinApi_Cell* cells;
	int width, height;
	char default_char;
	int default_back[3];
	int default_fore[3];
}Enguin_Surface;

// Surface
Enguin_Surface Enguin_Surface_Init(int width, int height, char ch, int wantF, int wantB, int fore[3], int back[3]);
void Enguin_Surface_Draw(Enguin_Surface* surface);
void Enguin_Surface_Update(Enguin_Surface* surface);

// Text
void Enguin_Text_Draw(Enguin_Surface* surface, int x, int y, char* text, int fore[3], int back[3]);

// Graphics
void Enguin_Pixel_Draw(Enguin_Surface* surface, int x, int y, char pixel, int fore[3], int back[3]);
void Enguin_Rect_Draw(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3]);

#endif
