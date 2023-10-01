#ifndef ENGUIN_IMAGE_H
#define ENGUIN_IMAGE_H

#include"../enguin_api/enguinApi.h"
#include"surface.h"

typedef struct{
    char ch;
    int fore[3];
    int back[3];
}Enguin_ImagePixel;

typedef struct{
    int w;
    int h;
    Enguin_ImagePixel* pixels;
}Enguin_Image;

Enguin_Image Enguin_Image_Create(int w, int h);
void Enguin_Image_Save(char* fn, Enguin_Image* img);
Enguin_Image Enguin_Image_Open(char* fn);
void Enguin_Image_Draw(Enguin_Surface* surface, Enguin_Image* img, int x, int y);

#endif