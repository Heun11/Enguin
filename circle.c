#include"Enguin/Enguin.h"

void CircleDraw(ENGUIN_Surface* s, int x_centre, int y_centre, int r)
{
    int x = r, y = 0;
    // printf("(%d, %d) ", x + x_centre, y + y_centre);
    ENGUIN_DrawPoint(s, x + x_centre, y + y_centre, 'X');

    if (r > 0)
    {
        // printf("(%d, %d) ", x + x_centre, -y + y_centre);
        ENGUIN_DrawPoint(s, -1*(x + x_centre), -y + y_centre, 'X');
        // printf("(%d, %d) ", y + x_centre, x + y_centre);
        ENGUIN_DrawPoint(s, y + x_centre, x + y_centre, 'X');
        // printf("(%d, %d)\n", -y + x_centre, x + y_centre);
        ENGUIN_DrawPoint(s, -y + x_centre, -1*(x + y_centre), 'X');
    }
     
    int P = 1 - r;
    while (x > y)
    {
        y++;
         
        if (P <= 0)
            P = P + 2*y + 1;
             
        else
        {
            x--;
            P = P + 2*y - 2*x + 1;
        }
         
        if (x < y)
            break;
         
        // printf("(%d, %d) ", x + x_centre, y + y_centre);
        ENGUIN_DrawPoint(s, x + x_centre, y + y_centre, 'X');
        // printf("(%d, %d) ", -x + x_centre, y + y_centre);
        ENGUIN_DrawPoint(s, -x + x_centre, y + y_centre, 'X');
        // printf("(%d, %d) ", x + x_centre, -y + y_centre);
        ENGUIN_DrawPoint(s, x + x_centre, -y + y_centre, 'X');
        // printf("(%d, %d)\n", -x + x_centre, -y + y_centre);
        ENGUIN_DrawPoint(s, -x + x_centre, -y + y_centre, 'X');
         
        if (x != y)
        {
            // printf("(%d, %d) ", y + x_centre, x + y_centre);
            ENGUIN_DrawPoint(s, y + x_centre, x + y_centre, 'X');
            // printf("(%d, %d) ", -y + x_centre, x + y_centre);
            ENGUIN_DrawPoint(s, -y + x_centre, x + y_centre, 'X');
            // printf("(%d, %d) ", y + x_centre, -x + y_centre);
            ENGUIN_DrawPoint(s, y + x_centre, -x + y_centre, 'X');
            // printf("(%d, %d)\n", -y + x_centre, -x + y_centre);
            ENGUIN_DrawPoint(s, -y + x_centre, -x + y_centre, 'X');
        }
    }
}

#include"Enguin/Enguin.h"

int main()
{
    ENGUIN_Surface s = ENGUIN_CreateSurface(50,50);
    ENGUIN_DrawSurface(&s);

    int run = 1;
    while(run){
        CircleDraw(&s, 24,24,10);

        ENGUIN_UpdateSurface(&s);        
        ENGUIN_Delay(1/120);
    }
    ENGUIN_KillSurface(&s);
    
    return 0;
}
