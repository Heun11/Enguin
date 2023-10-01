#include"Enguin/Enguin.h"

#define W 80
#define H 40

typedef struct{
    int x;
    int y;
    int isPressed;
}pointer;

int main(int argc, char** argv)
{
    printf("Welcome in Enguin Image Editor\n");
    printf("New file (0) or existing (!0) ?\n");
    int ex;
    scanf("%d", &ex);
    Enguin_Image img;
    char filename[64];
    if(ex==0){
        printf("Please enter size of new image (\"w h\")\n");
        int w, h;
        scanf("%d %d", &w, &h);
        printf("Please enter full name of file (\"test.engi\")\n");
        scanf("%60s", filename);
        img = Enguin_Image_Create(w, h);
    }
    else{
        printf("Please enter full name of file (\"test.engi\")\n");
        scanf("%60s", filename);
        img = Enguin_Image_Open(filename);
    }
    
	Enguin_Surface surf = Enguin_Surface_Init(W,H, ' ', 1, 1, (int[3]){10,10,10}, (int[3]){252, 250, 230});
	Enguin_Surface_Draw(&surf);
	
	int run = 1;
	const int fps = 60;
	const int frameDelay = 1000/fps;
	int frameStart, frameTime;
	char ch;
	char strFPS[64] = "FPS";

    pointer ptr = {4,4,0};
    int img_off = 6;

    int edit_progress = 0;
    char edit_buff[64]; 

    int saved = 1*fps;
    int savedC = 0;

	while(run){
		ch = EnguinApi_Input_KeyPressed();
		if(ch=='q'||ch=='Q'||ch==KEY_ESC){
			break;
		}

        if(!ptr.isPressed){
            if(ch=='w'||ch=='W'){
                ptr.y-=1;
            }
            if(ch=='s'||ch=='S'){
                ptr.y+=1;
            }
            if(ch=='a'||ch=='A'){
                ptr.x-=1;
            }
            if(ch=='d'||ch=='D'){
                ptr.x+=1;
            }
        }
        else{
            if(ch==KEY_UP){
                edit_progress+=1;
                if(edit_progress>6){
                    edit_progress = 0;
                }
		    }
            if(ch==KEY_DOWN){
                edit_progress-=1;
                if(edit_progress<0){
                    edit_progress = 6;
                }
		    }

            if(edit_progress>=0&&edit_progress<=2){
                //fore
                if(ch=='w'||ch=='W'){
                    img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]+=1;
                    if(img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]>255){
                        img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]=-1;
                    }
                }
                if(ch=='s'||ch=='S'){
                    img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]-=1;
                    if(img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]<-1){
                        img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[edit_progress]=255;
                    }
                }
            }
            else if(edit_progress>2&&edit_progress<=5){
                //back
                if(ch=='w'||ch=='W'){
                    img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]+=1;
                    if(img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]>255){
                        img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]=-1;
                    }
                }
                if(ch=='s'||ch=='S'){
                    img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]-=1;
                    if(img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]<-1){
                        img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[edit_progress-3]=255;
                    }
                }
            }
            else{
                if(ch>=32 && ch<=126){
                    img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].ch = ch;
                }
            }
        }

        if(ch==9){ // TAB
            ptr.isPressed = 0;
            edit_progress = 0;
		}
        if(ch=='\n'){
            if(ptr.x>=img_off && ptr.x<img_off+img.w && ptr.y>img_off && ptr.y<img_off+img.h+1){
                ptr.isPressed = 1;
            }
		}
        if(ch==' '||ch=='S'){
            Enguin_Image_Save(filename, &img);
            savedC = saved;
        }

		frameStart = EnguinApi_Utils_GetTicks();

		Enguin_Text_Draw(&surf, 1, 1, "Use AWSD to move, ENTER to enter edit mode, TAB to exit it, SPACE to save", (int[3]){0,0,0}, (int[3]){245, 66, 164});
        char ptr_buff[32];
        sprintf(ptr_buff, "%d %d", ptr.x, ptr.y);
        Enguin_Text_Draw(&surf, W-6, H-1, ptr_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});

        Enguin_Rect_Draw(&surf, img_off-1, img_off-1, img.w+2, img.h+2, '/', (int[3]){10,10,10}, (int[3]){227, 227, 20});
        Enguin_Image_Draw(&surf, &img, img_off, img_off);

		Enguin_Rect_Fill(&surf, ptr.x, ptr.y, 1, 1, '^', (int[3]){28, 27, 28}, (int[3]){245, 240, 191});

        if(savedC>0){
            Enguin_Text_Draw(&surf, 2, H-8, "File Saved!", (int[3]){0,0,0}, (int[3]){245, 66, 164});
            savedC-=1;
        }
        else{
            savedC = 0;
        }

        if(ptr.isPressed){
            Enguin_Pixel_Draw(&surf, 0, H-1, edit_progress+48, (int[3]){0,0,0}, (int[3]){245, 66, 164});
            Enguin_Text_Draw(&surf, 8, H-3, "Use arrows to progress in menu and use WS to edit values", (int[3]){0,0,0}, (int[3]){245, 66, 164});
            Enguin_Text_Draw(&surf, 7, H-2, "Note that if you want color you must set all 3 numbers", (int[3]){0,0,0}, (int[3]){245, 66, 164});
		    Enguin_Text_Draw(&surf, 10, H-1, "Writing mode activated", (int[3]){0,0,0}, (int[3]){245, 66, 164});
            Enguin_Text_Draw(&surf, 4, H-6, "EDITING:", (int[3]){0,0,0}, (int[3]){245, 66, 164});

            switch (edit_progress)
            {
            case 0:
                sprintf(edit_buff, "FORE_RED:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[0]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 1:
                sprintf(edit_buff, "FORE_GREEN:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[1]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 2:
                sprintf(edit_buff, "FORE_BLUE:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].fore[2]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 3:
                sprintf(edit_buff, "BACK_RED:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[0]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 4:
                sprintf(edit_buff, "BACK_GREEN:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[1]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 5:
                sprintf(edit_buff, "BACK_BLUE:%d", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].back[2]);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;

            case 6:
                sprintf(edit_buff, "CHAR:\'%c\'", img.pixels[(ptr.y-1-img_off)*img.w+(ptr.x-img_off)].ch);
		        Enguin_Text_Draw(&surf, 5, H-5, edit_buff, (int[3]){0,0,0}, (int[3]){245, 66, 164});
                break;
            
            default:
                break;
            }
        }

		Enguin_Text_Draw(&surf, 0, 0, strFPS, (int[3]){0,0,0}, (int[3]){245, 66, 164});
		Enguin_Surface_Update(&surf);

		frameTime = EnguinApi_Utils_GetTicks() - frameStart;
		if(frameDelay>frameTime){
			snprintf(strFPS, 7, "FPS:%d", (int)(1/(((float)frameDelay-(float)frameTime)/1000)));
			EnguinApi_Utils_Sleep((float)(frameDelay-frameTime));
		}
	}
	EnguinApi_Utils_Kill();
	return 0;
}
