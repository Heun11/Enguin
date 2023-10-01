#include"surface.h"

#define ABS(n) ((n > 0) ? n : (n * (-1)))

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

void Enguin_Line_Draw(Enguin_Surface* surface, int x1, int y1, int x2, int y2, char pixel, int fore[3], int back[3])
{
	int dx = x2 - x1;
    int dy = y2 - y1;
  
    int steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy);
  
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
  
    float X = x1;
    float Y = y1;
    for (int i = 0; i <= steps; i++) {
        Enguin_Pixel_Draw(surface, X, Y, pixel, fore, back);
        X += Xinc;
        Y += Yinc;
    }
}

void Enguin_Rect_Draw(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3])
{
	Enguin_Line_Draw(surface, x, y, x+w-1, y, pixel, fore, back);
	Enguin_Line_Draw(surface, x+w-1, y, x+w-1, y+h-1, pixel, fore, back);
	Enguin_Line_Draw(surface, x+w-1, y+h-1, x, y+h-1, pixel, fore, back);
	Enguin_Line_Draw(surface, x, y+h-1, x, y, pixel, fore, back);
}

void Enguin_Rect_Fill(Enguin_Surface* surface, int x, int y, int w, int h, char pixel, int fore[3], int back[3])
{
	for(int i=0;i<w;i++){
		for(int j=0;j<h;j++){
			Enguin_Pixel_Draw(surface, x+i, y+j, pixel, fore, back);
		}	
	}
}

void Enguin_Ellipse_Draw(Enguin_Surface* surface, int xc, int yc, int rx, int ry, char ch, int fore[3], int back[3])
{
	float dx, dy, d1, d2, x, y;
    x = 0;
    y = ry;
 
    d1 = (ry * ry)
         - (rx * rx * ry)
         + (0.25 * rx * rx);
    dx = 2 * ry * ry * x;
    dy = 2 * rx * rx * y;

    while (dx < dy) {
		Enguin_Pixel_Draw(surface, x + xc, y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, -x + xc, y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, x + xc, -y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, -x + xc, -y + yc, ch, fore, back);

        if (d1 < 0) {
            x++;
            dx = dx + (2 * ry * ry);
            d1 = d1 + dx + (ry * ry);
        }
        else {
            x++;
            y--;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d1 = d1 + dx - dy + (ry * ry);
        }
    }
    d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
         + ((rx * rx) * ((y - 1) * (y - 1)))
         - (rx * rx * ry * ry);
 
    while (y >= 0) {
		Enguin_Pixel_Draw(surface, x + xc, y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, -x + xc, y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, x + xc, -y + yc, ch, fore, back);
		Enguin_Pixel_Draw(surface, -x + xc, -y + yc, ch, fore, back);
 
        if (d2 > 0) {
            y--;
            dy = dy - (2 * rx * rx);
            d2 = d2 + (rx * rx) - dy;
        }
        else {
            y--;
            x++;
            dx = dx + (2 * ry * ry);
            dy = dy - (2 * rx * rx);
            d2 = d2 + dx - dy + (rx * rx);
        }
    }
}

void Enguin_Ellipse_Fill(Enguin_Surface* surface, int xc, int yc, int rx, int ry, char ch, int fore[3], int back[3])
{
	int hh = ry * ry;
	int ww = rx * rx;
	int hhww = hh * ww;
	int x0 = rx;
	int dx = 0;

	for (int x = -rx; x <= rx; x++)
		Enguin_Pixel_Draw(surface, xc + x, yc, ch, fore, back);

	for (int y = 1; y <= ry; y++)
	{
		int x1 = x0 - (dx - 1);
		for ( ; x1 > 0; x1--)
			if (x1*x1*hh + y*y*ww <= hhww)
				break;
		dx = x0 - x1;
		x0 = x1;

		for (int x = -x0; x <= x0; x++)
		{
			Enguin_Pixel_Draw(surface, xc + x, yc - y, ch, fore, back);
			Enguin_Pixel_Draw(surface, xc + x, yc + y, ch, fore, back);
		}
	}
	Enguin_Ellipse_Draw(surface, xc, yc, rx, ry, ch, fore, back);
}