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

void EnguinApi_Input_ResetTermios(void) 
{
	tcsetattr(0, TCSANOW, &old);
}

char EnguinApi_Input_Getch() 
{
	char ch;
	EnguinApi_Input_InitTermios(0);
	ch = getchar();
	EnguinApi_Input_ResetTermios();
	return ch;
}

int EnguinApi_Input_Kbhit(void)
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
	ch = EnguinApi_Input_Getch();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
	if(ch != EOF){
		ungetc(ch, stdin);
		return 1;
	} 
	return 0;
}


