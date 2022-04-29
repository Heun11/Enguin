// #include"Enguin/Enguin.h"

// void CircleDraw(ENGUIN_Surface* s, int x_centre, int y_centre, int r)
// {
//     int x = r, y = 0;
//     // printf("(%d, %d) ", x + x_centre, y + y_centre);
//     ENGUIN_DrawPoint(s, x + x_centre, y + y_centre, 'X');

//     if (r > 0)
//     {
//         // printf("(%d, %d) ", x + x_centre, -y + y_centre);
//         ENGUIN_DrawPoint(s, -1*(x + x_centre), -y + y_centre, 'X');
//         // printf("(%d, %d) ", y + x_centre, x + y_centre);
//         ENGUIN_DrawPoint(s, y + x_centre, x + y_centre, 'X');
//         // printf("(%d, %d)\n", -y + x_centre, x + y_centre);
//         ENGUIN_DrawPoint(s, -y + x_centre, -1*(x + y_centre), 'X');
//     }
     
//     int P = 1 - r;
//     while (x > y)
//     {
//         y++;
         
//         if (P <= 0)
//             P = P + 2*y + 1;
             
//         else
//         {
//             x--;
//             P = P + 2*y - 2*x + 1;
//         }
         
//         if (x < y)
//             break;
         
//         // printf("(%d, %d) ", x + x_centre, y + y_centre);
//         ENGUIN_DrawPoint(s, x + x_centre, y + y_centre, 'X');
//         // printf("(%d, %d) ", -x + x_centre, y + y_centre);
//         ENGUIN_DrawPoint(s, -x + x_centre, y + y_centre, 'X');
//         // printf("(%d, %d) ", x + x_centre, -y + y_centre);
//         ENGUIN_DrawPoint(s, x + x_centre, -y + y_centre, 'X');
//         // printf("(%d, %d)\n", -x + x_centre, -y + y_centre);
//         ENGUIN_DrawPoint(s, -x + x_centre, -y + y_centre, 'X');
         
//         if (x != y)
//         {
//             // printf("(%d, %d) ", y + x_centre, x + y_centre);
//             ENGUIN_DrawPoint(s, y + x_centre, x + y_centre, 'X');
//             // printf("(%d, %d) ", -y + x_centre, x + y_centre);
//             ENGUIN_DrawPoint(s, -y + x_centre, x + y_centre, 'X');
//             // printf("(%d, %d) ", y + x_centre, -x + y_centre);
//             ENGUIN_DrawPoint(s, y + x_centre, -x + y_centre, 'X');
//             // printf("(%d, %d)\n", -y + x_centre, -x + y_centre);
//             ENGUIN_DrawPoint(s, -y + x_centre, -x + y_centre, 'X');
//         }
//     }
// }

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
    ENGUIN_Surface s = ENGUIN_CreateSurface(50,50);
    ENGUIN_DrawSurface(&s);

    // float x = 0.0f;

    int run = 1;
    while(run){
        CircleDraw(&s, 24,24,20);

        // for(int i=0;i<128*128;i++){
        //     ENGUIN_DrawPoint(&s, (int)x, i/128, 'X');
        // }

        // x+=0.001f;

        ENGUIN_UpdateSurface(&s);        
        ENGUIN_Delay(1/30);
    }
    ENGUIN_KillSurface(&s);

    return 0;
}
