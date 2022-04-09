#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

// #include <termios.h>
// #include <fcntl.h>

// int getch_echo(int echo){
//       struct termios oldt, newt;
//       int ch;
//       tcgetattr( STDIN_FILENO, &oldt );
//       newt = oldt;
//       newt.c_lflag &= ~ICANON;
//       if(echo)
// 	newt.c_lflag &=  ECHO;
//       else
// 	newt.c_lflag &= ~ECHO;
//       tcsetattr( STDIN_FILENO, TCSANOW, &newt );
//       ch = getchar();
//       tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
//       return ch;
//       }
      
//     int getch(){
//       getch_echo(0);
//       }
      
//     int getche(){
//       getch_echo(1);
//       }

//     int kbhit(){
//       struct termios oldt, newt;
//       int ch;
//       int oldf;    
//       tcgetattr(STDIN_FILENO, &oldt);
//       newt = oldt;
//       newt.c_lflag &= ~(ICANON | ECHO);
//       tcsetattr(STDIN_FILENO, TCSANOW, &newt);
//       oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
//       fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);    
//       ch = getchar();    
//       tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
//       fcntl(STDIN_FILENO, F_SETFL, oldf);    
//       if(ch != EOF){
// 	ungetc(ch, stdin);
// 	return 1;
// 	}    
//       return 0;
//       }


// int main(int argc, char const *argv[])
// {
// 	while(1){
// 		if(kbhit()){
// 			int c = getch();
// 			printf("Pressed ASCII %d\n", c);
// 		}
// 	}
// 	return 0;
// }

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <linux/input.h>
#include <fcntl.h>
#include <signal.h>

#define INPUT_DIR "/dev/input/"

static int is_char_device(const struct dirent *file){
    struct stat filestat;
    char filename[512];
    int err;

    snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, file->d_name);

    err = stat(filename, &filestat);
    if(err){
        return 0;
    }

    return S_ISCHR(filestat.st_mode);
}

char *get_keyboard_event_file(void){
    char *keyboard_file = NULL;
    int num, i;
    struct dirent **event_files;
    char filename[512];

    num = scandir(INPUT_DIR, &event_files, &is_char_device, &alphasort);
    if(num < 0){
        return NULL;
    }

    else {
        for(i = 0; i < num; ++i){
            int32_t event_bitmap = 0;
            int fd;
            int32_t kbd_bitmap = KEY_A | KEY_B | KEY_C | KEY_Z; 

            snprintf(filename, sizeof(filename), "%s%s", INPUT_DIR, event_files[i]->d_name);
            fd = open(filename, O_RDONLY);

            if(fd == -1){
                perror("open");
                continue;
            }

            ioctl(fd, EVIOCGBIT(0, sizeof(event_bitmap)), &event_bitmap);
            if((EV_KEY & event_bitmap) == EV_KEY){

                ioctl(fd, EVIOCGBIT(EV_KEY, sizeof(event_bitmap)), &event_bitmap);
                if((kbd_bitmap & event_bitmap) == kbd_bitmap){
                    keyboard_file = strdup(filename);
                    close(fd);
                    break;
                }

            }

            close(fd);

        }
    }
    
    for(i = 0; i < num; ++i){
        free(event_files[i]);
    }

    free(event_files);
    return keyboard_file;
}

void INThandler(){
	printf("ended\n");
	system("stty echo");
  	exit(0);
}

int main()
{
        char *devname = get_keyboard_event_file();
        int device = open(devname, O_RDONLY);
        struct input_event ev;

        signal(SIGINT, INThandler);
        system("stty -echo");
        while(1)
        {
                read(device,&ev, sizeof(ev));
                if(ev.type == 1 && ev.value == 1){
                        printf("Key: %i State: %i\n",ev.code,ev.value);
                }
        }
        system("stty echo");
}