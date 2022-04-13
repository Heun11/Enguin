#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
 
static struct termios old, current;

void ENGUIN_UTILS_InitTermios(int echo) 
{
  tcgetattr(0, &old);
  current = old;
  current.c_lflag &= ~ICANON;
  if (echo) {
      current.c_lflag |= ECHO;
  } else {
      current.c_lflag &= ~ECHO;
  }
  tcsetattr(0, TCSANOW, &current);
}

void ENGUIN_UTILS_ResetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

char ENGUIN_Getch() 
{
  char ch;
  ENGUIN_UTILS_InitTermios(0);
  ch = getchar();
  ENGUIN_UTILS_ResetTermios();
  return ch;
}

int ENGUIN_Kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}


int main(int argc, char *argv[])
{
    system("stty -echo");
    char c;
    while(1){
        if(ENGUIN_Kbhit()){
            c = ENGUIN_Getch();
            if(c=='\033'){
                ENGUIN_Getch();
                switch(ENGUIN_Getch()){
                    case 'A':
                        printf("Arrow up\n");
                        break;
                    case 'B':
                        printf("Arrow down\n");
                        break;
                    case 'C':
                        printf("Arrow right\n");
                        break;
                    case 'D':
                        printf("Arrow left\n");
                        break;
                }
            }
            else if(c=='q'){
                break;
            }
        }
        usleep(1/30*1000000);
    }
    system("stty echo");
    return 0;
}
