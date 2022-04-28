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

typedef struct{
	int len;
	char* str;
}ENGUIN_Buffer;

ENGUIN_Buffer ENGUIN_Buffer_init()
{
	ENGUIN_Buffer arr;
	arr.len = 1;
	arr.str = (char*)malloc(1);
	arr.str[0] = '\0';
	return arr;
}

void ENGUIN_Buffer_add(ENGUIN_Buffer* arr, char* str, int strSize)
{
	arr->len += strSize;
	arr->str = (char*)realloc(arr->str, arr->len);
	strcat(arr->str, str);
}

void ENGUIN_Buffer_pop(ENGUIN_Buffer* arr, int strSize)
{
	arr->len -= strSize-1;
	arr->str = (char*)realloc(arr->str, arr->len);
	arr->str[0] = '\0';
}

int main()
{
	ENGUIN_Buffer arr = ENGUIN_Buffer_init();
	printf("%s\n", arr.str);
	ENGUIN_Buffer_add(&arr, "debil", strlen("debil"));
	ENGUIN_Buffer_add(&arr, "retard", strlen("retard"));
	printf("%s %d\n", arr.str, arr.len);
	ENGUIN_Buffer_pop(&arr, arr.len);
	return 0;
}
