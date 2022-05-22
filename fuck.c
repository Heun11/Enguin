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

// #include <sys/time.h>

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// typedef struct{
// 	int len;
// 	char* str;
// }ENGUIN_Buffer;

// ENGUIN_Buffer ENGUIN_Buffer_init()
// {
// 	ENGUIN_Buffer arr;
// 	arr.len = 1;
// 	arr.str = (char*)malloc(1);
// 	arr.str[0] = '\0';
// 	return arr;
// }

// void ENGUIN_Buffer_add(ENGUIN_Buffer* arr, char* str, int strSize)
// {
// 	arr->len += strSize;
// 	arr->str = (char*)realloc(arr->str, arr->len);
// 	strcat(arr->str, str);
// }

// void ENGUIN_Buffer_pop(ENGUIN_Buffer* arr, int strSize)
// {
// 	arr->len -= strSize;
// 	arr->str = (char*)realloc(arr->str, arr->len);
// 	arr->str[arr->len-1] = '\0';
// }

// int main()
// {
// 	ENGUIN_Buffer arr = ENGUIN_Buffer_init();
// 	printf("%s %d\n", arr.str, arr.len);
// 	ENGUIN_Buffer_add(&arr, "debil", strlen("debil"));
// 	ENGUIN_Buffer_add(&arr, "retard", strlen("retard"));
// 	printf("%s %d\n", arr.str, arr.len);
// 	ENGUIN_Buffer_pop(&arr, 6);
// 	printf("%s %d\n", arr.str, arr.len);
// 	return 0;
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//TODO -> array of strings (dynamic) **fuck

// typedef struct{
// 	int size;
// 	int maxLength;
// 	char* string;
// }ENGUIN_Buffer;

// ENGUIN_Buffer ENGUIN_BufferInit(int size, int maxLength)
// {
// 	ENGUIN_Buffer buff;
// 	buff.size = size;
// 	buff.maxLength = maxLength;
// 	buff.string = (char*)malloc(size*maxLength*sizeof(char));
// 	for(int i=0;i<size;i++){
// 		*(buff.string+i*maxLength) = '\0';
// 	}
// 	return buff;
// }

// char* ENGUIN_BufferGet(ENGUIN_Buffer* buff, int id)
// {
// 	return buff->string+id*buff->maxLength;
// }

// void ENGUIN_BufferSet(ENGUIN_Buffer* buff, int id, char* str)
// {
// 	int i;
// 	if(strlen(str)<=buff->maxLength){
// 		for(i=0;i<buff->maxLength;i++){
// 			if(i<=strlen(str)){
// 				*(buff->string+id*buff->maxLength+i) = *(str+i);
// 			}
// 			else{
// 				*(buff->string+id*buff->maxLength+i) = ' ';
// 			}
// 		}
// 	}
// }

// int main(int argc, char const *argv[])
// {
// 	ENGUIN_Buffer test = ENGUIN_BufferInit(3, 9);

// 	ENGUIN_BufferSet(&test, 0, "debil");
// 	ENGUIN_BufferSet(&test, 1, "retard");
// 	ENGUIN_BufferSet(&test, 2, "autik");

// 	ENGUIN_BufferSet(&test, 2, "hlupak");

// 	for(int i=0;i<test.size;i++){
// 		printf("%s\n", ENGUIN_BufferGet(&test, i));
// 	}

// 	printf("%d", strcmp(ENGUIN_BufferGet(&test, 0), "debil"));

// 	return 0;
// }





//////////////////////////////////////////////////////


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


#include"Enguin/test.h"
#include<sys/time.h>
#include<time.h>

int main()
{
	struct timeval t1, t2;
	double elapsedTime, delta;
	char deltaStr[20] = "debil";
	srand(time(0));

	EnguinApi_Canvas canvas = EnguinApi_Canvas_Create(60,30);
	while(1){

		gettimeofday(&t1, NULL);
		
		for(int i=0;i<60;i++){
			for(int j=0;j<29;j++){
				EnguinApi_Canvas_MoveTo(&canvas, i, j);
				canvas.cells[j*60+i].ch = EnguinApi_Utils_RandomNumber(33, 126);
				canvas.cells[j*60+i].isModified = 1;
			}
		}
		EnguinApi_Canvas_Flush(&canvas);

		snprintf(deltaStr, 20, "%lf", (1/delta));
		EnguinApi_Canvas_MoveTo(&canvas, 0, 29);
		EnguinApi_Canvas_Write(&canvas, deltaStr);
		
		usleep(16666);
		
		gettimeofday(&t2, NULL);

		elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
		elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

		delta = elapsedTime/1000;

		//EnguinApi_Canvas_Flush(&canvas);

	}
	return 0;
}
