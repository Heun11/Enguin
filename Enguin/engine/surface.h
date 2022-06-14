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
	int default_front[3];
}Enguin_Surface;

Enguin_Surface Enguin_Surface_Init(int, int, char, int[3], int[3]);
void Enguin_Surface_Draw(Enguin_Surface*);
void Enguin_Surface_Update(Enguin_Surface*);

#endif
