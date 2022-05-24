#pragma once
#ifndef INPUT_H
#define INPUT_H

//#include<ctype.h>
//#include<sys/ioctl.h>
#include<termios.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

void EnguinApi_Input_InitTermios(int);
void EnguinApi_Input_ResetTermios(void);
char EnguinApi_Input_Getch();
int EnguinApi_Input_Kbhit(void);

#endif
