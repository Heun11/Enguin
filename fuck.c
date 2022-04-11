// #include<stdio.h>
// #include<stdlib.h>
// #include<unistd.h>
// #include<string.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <dirent.h>
// #include <sys/ioctl.h>
// #include <linux/input.h>
// #include <fcntl.h>
// #include <signal.h>
// #include <pthread.h>

// #define INPUT_DIR "/dev/input/"

// static int ENGUIN_UTILS_IsCharDevice(const struct dirent *file){
//     struct stat filestat;
//     char filename[512];
//     int err;

//     snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, file->d_name);

//     err = stat(filename, &filestat);
//     if(err){
//         return 0;
//     }

//     return S_ISCHR(filestat.st_mode);
// }

// char* ENGUIN_UTILS_GetKeyboardEventFile(void){
//     char *keyboard_file = NULL;
//     int num, i;
//     struct dirent **event_files;
//     char filename[512];

//     num = scandir(INPUT_DIR, &event_files, &ENGUIN_UTILS_IsCharDevice, &alphasort);
//     if(num < 0){
//         return NULL;
//     }

//     else {
//         for(i = 0; i < num; ++i){
//             int32_t event_bitmap = 0;
//             int fd;
//             int32_t kbd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z; 

//             snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, event_files[i]->d_name);
//             fd = open(filename, O_RDONLY);

//             if(fd == -1){
//                 perror("open");
//                 continue;
//             }

//             ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);
//             if((EV_KEY & event_bitmap) == EV_KEY){

//                 ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(event_bitmap)), &event_bitmap);
//                 if((kbd_bitmap & event_bitmap) == kbd_bitmap){
//                     keyboard_file = strdup(filename);
//                     close(fd);
//                     break;
//                 }

//             }

//             close(fd);

//         }
//     }
    
//     for(i = 0; i < num; ++i){
//         free(event_files[i]);
//     }

//     free(event_files);
//     return keyboard_file;
// }

// void INThandler(){
// 	printf("ended\n");
// 	system("stty echo");
//   	exit(0);
// }

// int checkInput(int device)
// {
//     struct input_event ev;
//     read(device,&ev, sizeof(ev));
//     if(ev.type==1&&ev.value>0){
//         return ev.code;
//     }
//     else{
//         return -1;
//     }
// }

// typedef struct{
//     int value;
// }ENGUIN_UTILS_Key;

// void* ENGUIN_UTILS_KeyThread(void *args)
// {
//     char *devname = ENGUIN_UTILS_GetKeyboardEventFile();
//     int device = open(devname, O_RDONLY);
    
//     ENGUIN_UTILS_Key* key = args;

//     while(1){
//         int k = checkInput(device);
//         if(k!=-1){
//             key->value = k;
//             usleep((1/60)*1000000);
//             key->value = -1;
//         }
//     }

//     free(key);
// }

// int main()
// {
//         ENGUIN_UTILS_Key *key = malloc(sizeof *key);
//         key->value = -1;
//         int last_k, k;

//         pthread_t thread_id;
//         pthread_create(&thread_id, NULL, ENGUIN_UTILS_KeyThread, key);

//         signal(SIGINT, INThandler);
//         system("stty -echo");
//         while(1)
//         {
//             k = key->value;
//             if(k!=last_k){
//                 last_k = k;
//                 if(last_k!=-1){
//                     printf("%d\n", k);
//                 }
//             }

//             usleep((1/60)*1000000);
//         }
//         system("stty echo");
// }

// ################################################################################################################################

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <fcntl.h>
 
static struct termios old, current;

void initTermios(int echo) 
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

void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

char getch() 
{
  char ch;
  initTermios(0);
  ch = getchar();
  resetTermios();
  return ch;
}

int kbhit(void)
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
    int c;
    while(1){
        if(kbhit()){
            c = getch();
            if(c=='q'){
                break;
            }
            printf("%d\n", c);
        }
    }
    return 0;
}