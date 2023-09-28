#include"Enguin/Enguin.h"
#include<sys/time.h>

#define W 50
#define H 30

int main()
{
	EnguinApi_Canvas canvas = EnguinApi_Canvas_Create(W,H,1,1,(int[3]){200, 198, 222},(int[3]){10, 20, 15}, ' ');
	EnguinApi_Canvas_Flush(&canvas);
	EnguinApi_Canvas_CursorHide();
	EnguinApi_Canvas_InputHide();
    // EnguinApi_Input_InitTermios(1);

	const int FPS = 60;
	const int frameDelay = 1000/FPS;


	time_t t = time(NULL);
	__uint32_t frameStart;
	int frameTime;

	char ch;
	char strFPS[64] = "FPS";

	float x = 22;
	float y = 15;

    float prevx = x;
    float prevy = y;

    int jump = 0;
    float jh = 6;

    float box1x = 0.1f;
    float box1y = 14;
    float box1prevx = x;
    float boxs = 0.3f;

	while(1){
	
		ch = EnguinApi_Input_KeyPressed();
		if(ch=='q'||ch=='Q'||ch==KEY_ESC){
			break;
		}

		frameStart = time(NULL)*1000;

        if(ch==' '){
            jump = 1;
        }

        if(jump){
            if(y>=15-jh){
                prevy = y;
                y-=0.2f;
            }
            else{
                prevy = y;
                y = 15;
                jump = 0;
            }
        }

        box1prevx = box1x;
        box1x -= boxs;
        if(box1x<=0){
            box1prevx = box1x;
            box1x = W-1;
        }

        // dino
		EnguinApi_Canvas_Erease(&canvas, (int)prevx, (int)prevy, (int)prevx, (int)prevy);
		EnguinApi_Canvas_MoveTo(&canvas, (int)x, (int)y);
		EnguinApi_Canvas_Write(&canvas, "D", (int[3]){-1,-1,-1}, (int[3]){-1,-1,-1});

        // box
		EnguinApi_Canvas_Erease(&canvas, (int)box1prevx, (int)box1y, (int)box1prevx+1, (int)box1y+1);
		EnguinApi_Canvas_MoveTo(&canvas, (int)box1x, (int)box1y);
		EnguinApi_Canvas_Write(&canvas, "##", (int[3]){-1,-1,-1}, (int[3]){-1,-1,-1});
		EnguinApi_Canvas_MoveTo(&canvas, (int)box1x, (int)box1y+1);
		EnguinApi_Canvas_Write(&canvas, "##", (int[3]){-1,-1,-1}, (int[3]){-1,-1,-1});

        for(int i=0;i<W;i++){
            for(int j=0;j<H;j++){
		        EnguinApi_Canvas_MoveTo(&canvas, 0+i, 16+j);
		        EnguinApi_Canvas_Write(&canvas, " ", (int[3]){-1,-1,-1}, (int[3]){235, 52, 225});
            }
        }

		EnguinApi_Canvas_Erease(&canvas, 0,0, 5,0);
		EnguinApi_Canvas_MoveTo(&canvas, 0,0);
		EnguinApi_Canvas_Write(&canvas, strFPS, (int[3]){50, 151, 168}, (int[3]){29, 31, 29});
		EnguinApi_Canvas_Flush(&canvas);

		frameTime = time(NULL)*1000 - frameStart;
		if(frameDelay>frameTime){
			snprintf(strFPS, 7, "FPS:%d", (int)(1/(((float)frameDelay-(float)frameTime)/1000)));
			EnguinApi_Utils_Sleep((float)(frameDelay-frameTime));
		}
	}

	EnguinApi_Canvas_InputShow();
	EnguinApi_Canvas_CursorShow();
	EnguinApi_Utils_Kill();

	return 0;
}
