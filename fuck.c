#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// #include <ctype.h>
// #include <sys/ioctl.h>
// #include <termios.h>
// #include <fcntl.h>
 
// static struct termios old, current;

// void ENGUIN_UTILS_InitTermios(int echo) 
// {
//   tcgetattr(0, &old);
//   current = old;
//   current.c_lflag &= ~ICANON;
//   if (echo) {
//       current.c_lflag |= ECHO;
//   } else {
//       current.c_lflag &= ~ECHO;
//   }
//   tcsetattr(0, TCSANOW, &current);
// }

// void ENGUIN_UTILS_ResetTermios(void) 
// {
//   tcsetattr(0, TCSANOW, &old);
// }

// char ENGUIN_Getch() 
// {
//   char ch;
//   ENGUIN_UTILS_InitTermios(0);
//   ch = getchar();
//   ENGUIN_UTILS_ResetTermios();
//   return ch;
// }

// int ENGUIN_Kbhit(void)
// {
//   struct termios oldt, newt;
//   int ch;
//   int oldf;
 
//   tcgetattr(STDIN_FILENO, &oldt);
//   newt = oldt;
//   newt.c_lflag &= ~(ICANON | ECHO);
//   tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//   oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
//   fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
//   ch = getchar();
 
//   tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//   fcntl(STDIN_FILENO, F_SETFL, oldf);
 
//   if(ch != EOF)
//   {
//     ungetc(ch, stdin);
//     return 1;
//   }
 
//   return 0;
// }


// int main(int argc, char *argv[])
// {
//     system("stty -echo");
//     char c;
//     while(1){
//         if(ENGUIN_Kbhit()){
//             c = ENGUIN_Getch();
//             if(c=='\033'){
//                 ENGUIN_Getch();
//                 switch(ENGUIN_Getch()){
//                     case 'A':
//                         printf("Arrow up\n");
//                         break;
//                     case 'B':
//                         printf("Arrow down\n");
//                         break;
//                     case 'C':
//                         printf("Arrow right\n");
//                         break;
//                     case 'D':
//                         printf("Arrow left\n");
//                         break;
//                 }
//             }
//             else if(c=='q'){
//                 break;
//             }
//         }
//         usleep(1/30*1000000);
//     }
//     system("stty echo");
//     return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// int main ()
// {
//     struct timeval t1, t2;
//     double elapsedTime, delta;

//     //start timer
//     gettimeofday(&t1, NULL);

//     printf("debil\n");

//     //stop timer
//     gettimeofday(&t2, NULL);

//     //compute
//     elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
//     elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

//     //convert to seconds
//     delta = elapsedTime /1000;
    
//     printf("%lf\n", delta);

//     return(0);
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include"Enguin/Enguin.h"
// #include<sys/time.h>
// #include<time.h>

// int main()
// {
// 	struct timeval t1, t2;
// 	double elapsedTime, delta;
// 	char deltaStr[20] = "debil";
// 	int ch;
// 	srand(time(0));

// 	char* surf1 = (char)malloc(30*30);
// 	char* surf2 = (char)malloc(30*30);

// 	for(int i=0;i<30*30;i++){
// 		surf1[i] = '-';
// 		surf2[i] = '-';
// 	}

// 	EnguinApi_Canvas canvas = EnguinApi_Canvas_Create(60,30);
// 	EnguinApi_Canvas_CursorHide();
// 	EnguinApi_Canvas_InputHide();
// 	while(1){

// 		gettimeofday(&t1, NULL);
		
// 		//for(int i=0;i<60;i++){
// 		//	for(int j=0;j<29;j++){
// 		//		EnguinApi_Canvas_MoveTo(&canvas, i, j);
// 		//		canvas.cells[j*60+i].ch = EnguinApi_Utils_RandomNumber(33, 126);
// 		//		canvas.cells[j*60+i].isModified = 1;
// 		//	}
// 		//}
		
// 		EnguinApi_Canvas_SetForeground(&canvas, (int[3]){7, 48, 245});
// 		EnguinApi_Canvas_SetBackground(&canvas, (int[3]){245,127,194});

// 		ch = EnguinApi_Input_KeyPressed();
// 		if(ch==KEY_UP){
// 			EnguinApi_Canvas_MoveTo(&canvas, 0,0);
// 			EnguinApi_Canvas_Write(&canvas, "debil");
// 		}
// 		else if(ch==KEY_DOWN){
// 			EnguinApi_Canvas_MoveTo(&canvas, 0,0);
// 			EnguinApi_Canvas_Write(&canvas, "autik");
// 		}
// 		else if(ch=='q'||ch=='Q'||ch==KEY_ESC){
// 			break;
// 		}

// 		EnguinApi_Canvas_Flush(&canvas);

// 		snprintf(deltaStr, 20, "%lf", (1/delta));
// 		EnguinApi_Canvas_MoveTo(&canvas, 0, 29);
// 		EnguinApi_Canvas_Write(&canvas, deltaStr);
		
// 		//usleep(16666);
// 		EnguinApi_Utils_Sleep((float)1/30);

// 		gettimeofday(&t2, NULL);

// 		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
// 		elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

// 		delta = elapsedTime/1000;

// 		//EnguinApi_Canvas_Flush(&canvas);

// 	}
// 	EnguinApi_Canvas_InputShow();
// 	EnguinApi_Canvas_CursorShow();

// 	return 0;
// }


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

	const int FPS = 30;
	const int frameDelay = 1000/FPS;


	time_t t = time(NULL);
	__uint32_t frameStart;
	int frameTime;

	char ch;
	char strFPS[64] = "FPS";

	float x = 0.1;
	float y = 0.1;

	float prevx = x;
	float prevy = y;

	float sx = 0.7;
	float sy = 0.5;

	while(1){
	
		ch = EnguinApi_Input_KeyPressed();
		if(ch=='q'||ch=='Q'||ch==KEY_ESC){
			break;
		}
		
		if(x>=W-1||x<=0){
			sx*=-1;
		}
		if(y>=H-1||y<=0){
			sy*=-1;
		}

		prevx = x;
		prevy = y;

		x+=sx;
		y+=sy;

		frameStart = time(NULL)*1000;

		// EnguinApi_Canvas_Erease(&canvas, (int)prevx, (int)prevy, (int)prevx, (int)prevy);
		EnguinApi_Canvas_MoveTo(&canvas, (int)x, (int)y);
		EnguinApi_Canvas_Write(&canvas, "$", (int[3]){-1,-1,-1}, (int[3]){-1,-1,-1});

		EnguinApi_Canvas_Erease(&canvas, 0,0, 5,0);
		EnguinApi_Canvas_MoveTo(&canvas, 0,0);
		EnguinApi_Canvas_Write(&canvas, strFPS, (int[3]){50, 151, 168}, (int[3]){-1,-1,-1});
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
