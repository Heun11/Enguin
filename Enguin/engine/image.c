#include"image.h"

Enguin_Image Enguin_Image_Create(int w, int h)
{
    Enguin_Image img = {w,h,NULL};
    img.pixels = malloc(sizeof(Enguin_ImagePixel)*w*h);
    for(int i=0;i<w*h;i++){
        img.pixels[i].ch = ' ';
        for(int j=0;j<3;j++){
            img.pixels[i].back[j] = -1;
            img.pixels[i].fore[j] = -1;
        }
    }
    return img;
}

void Enguin_Image_Save(char* fn, Enguin_Image* img)
{
    FILE* file;
    file = fopen(fn, "w");
    if (file == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }
    char buff[64];
    sprintf(buff, "%d %d\n", img->w, img->h);
    fprintf(file, "%s", buff);

    for(int i=0;i<img->h*img->w;i++){
        sprintf(buff, "%d %d %d %d %d %d %d\n", (int)img->pixels[i].ch, img->pixels[i].fore[0], img->pixels[i].fore[1], img->pixels[i].fore[2],img->pixels[i].back[0], img->pixels[i].back[1], img->pixels[i].back[2]);
        fprintf(file, "%s", buff);
    }
    fclose(file);
}

Enguin_Image Enguin_Image_Open(char* fn)
{
    FILE* file;
    int w, h;
    file = fopen(fn, "r");
    if (file == NULL) {
        fprintf(stderr, "\nError opening file\n");
        exit(1);
    }

    fscanf(file, "%d %d", &w, &h);
    Enguin_Image img = Enguin_Image_Create(w, h);
    for(int i=0;i<h*w;i++){
		fscanf(file, "%d %d %d %d %d %d %d", (int*)&img.pixels[i].ch, &img.pixels[i].fore[0], &img.pixels[i].fore[1], &img.pixels[i].fore[2],&img.pixels[i].back[0], &img.pixels[i].back[1], &img.pixels[i].back[2]);
	}
    fclose(file);
    return img;
}

void Enguin_Image_Draw(Enguin_Surface* surface, Enguin_Image* img, int x, int y)
{
    for(int i=0;i<img->w;i++){
        for(int j=0;j<img->h;j++){
            Enguin_Pixel_Draw(surface, x+i, y+j, img->pixels[j*img->w+i].ch, img->pixels[j*img->w+i].fore, img->pixels[j*img->w+i].back);
        }
    }
}

