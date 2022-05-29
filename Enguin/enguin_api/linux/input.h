#pragma once
#ifndef INPUT_H
#define INPUT_H

#include<termios.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

#define KEY_ESC 1
#define KEY_UP 2
#define KEY_DOWN 3
#define KEY_LEFT 4
#define KEY_RIGHT 5

void EnguinApi_Input_InitTermios(int);
void EnguinApi_Input_ResetTermios(void);
char EnguinApi_Input_Getch();
int EnguinApi_Input_Kbhit(void);
int EnguinApi_Input_KeyPressed();

#endif
