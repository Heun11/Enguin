#pragma once
#ifndef CANVAS_H
#define CANVAS_H

#include"utils.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

//Cell
typedef struct{
	int isModified;
	char ch;
	int x, y;
	int wantBack;
	int wantFore;
	int foreground[3];
	int background[3];

	char default_ch;
	int default_background[3];
	int default_foreground[3];
}EnguinApi_Cell;

EnguinApi_Cell EnguinApi_Cell_Create(char, int, int, int, int, int[3], int[3]);
void EnguinApi_Cell_Reset(EnguinApi_Cell*);
void EnguinApi_Cell_SetForeground(EnguinApi_Cell*, int[3]);
void EnguinApi_Cell_ResetForeground(EnguinApi_Cell*);
void EnguinApi_Cell_SetBackground(EnguinApi_Cell*, int[3]);
void EnguinApi_Cell_ResetBackground(EnguinApi_Cell*);
char* EnguinApi_Cell_ToString(EnguinApi_Cell*);

//Canvas
typedef struct{
	EnguinApi_Cell* cells;
	EnguinApi_Utils_Buffer lastFrame;
	int width, height;
	int cursorX, cursorY;
	int wantBack;
	int wantFore;
	int background[3];
	int foreground[3];

	char default_ch;
	int default_background[3];
	int default_foreground[3];
}EnguinApi_Canvas;

EnguinApi_Canvas EnguinApi_Canvas_Create(int, int, int, int, int[3], int[3], char);
void EnguinApi_Canvas_Write(EnguinApi_Canvas*, char*, int[3], int[3]);
void EnguinApi_Canvas_Flush(EnguinApi_Canvas*);
void EnguinApi_Canvas_MoveTo(EnguinApi_Canvas*, int, int);
void EnguinApi_Canvas_SetForeground(EnguinApi_Canvas*, int[3]);
void EnguinApi_Canvas_SetBackground(EnguinApi_Canvas*, int[3]);
void EnguinApi_Canvas_Erease(EnguinApi_Canvas* , int, int, int, int);
void EnguinApi_Canvas_CursorHide();
void EnguinApi_Canvas_CursorShow();
void EnguinApi_Canvas_InputHide();
void EnguinApi_Canvas_InputShow();

#endif
