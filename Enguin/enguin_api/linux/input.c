#include"input.h"

static struct termios old, current;

void EnguinApi_Input_InitTermios(int echo)
{
	tcgetattr(0, &old);
	current = old;
	current.c_lflag &= ~ICANON;
	if(echo){
		current.c_lflag |= ECHO;
	}
	else{
		current.c_lflag &= ~ECHO;
	}
	tcsetattr(0, TCSANOW, &current);
}
