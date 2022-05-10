#include"Enguin/Enguin.h"

void CircleDraw(ENGUIN_Surface* s, int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
        // putpixel(x0 + x, y0 + y, 7);
        ENGUIN_DrawPoint(s, x0 + x, y0 + y, 'X');
        // putpixel(x0 + y, y0 + x, 7);
        ENGUIN_DrawPoint(s, x0 + y, y0 + x, 'X');
        // putpixel(x0 - y, y0 + x, 7);
        ENGUIN_DrawPoint(s, x0 - y, y0 + x, 'X');
        // putpixel(x0 - x, y0 + y, 7);
        ENGUIN_DrawPoint(s, x0 - x, y0 + y, 'X');
        // putpixel(x0 - x, y0 - y, 7);
        ENGUIN_DrawPoint(s, x0 - x, y0 - y, 'X');
        // putpixel(x0 - y, y0 - x, 7);
        ENGUIN_DrawPoint(s, x0 - y, y0 - x, 'X');
        // putpixel(x0 + y, y0 - x, 7);
        ENGUIN_DrawPoint(s, x0 + y, y0 - x, 'X');
        // putpixel(x0 + x, y0 - y, 7);
        ENGUIN_DrawPoint(s, x0 + x, y0 - y, 'X');
 
        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
         
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

int main()
{
    ENGUIN_Surface s = ENGUIN_CreateSurface(127,127);
    ENGUIN_DrawSurface(&s);

    float r = 0;

    int run = 1;
    while(run){
        // CircleDraw(&s, 63,63,r);
        // CircleDraw(&s, 63,63,r-4);
        // CircleDraw(&s, 63,63,r-8);

        for(int i=0;i<10*4;i+=4){
            CircleDraw(&s, 63,63,r-i);
        }

        r+=0.001f;
        if(r-10*4>63){
            r=0;
        }

        ENGUIN_UpdateSurface(&s);        
        // ENGUIN_Delay(1/5);
    }
    ENGUIN_KillSurface(&s);

    return 0;
}
