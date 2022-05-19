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
	int foreground[3];
	int background[3];
}EnguinApi_Cell;

EnguinApi_Cell EnguinApi_Cell_Create(char, int, int);
void EnguinApi_Cell_Reset(EnguinApi_Cell*);
char* EnguinApi_Cell_ToString(EnguinApi_Cell*);

//Canvas
typedef struct{
	EnguinApi_Cell* cells;
	EnguinApi_Utils_Buffer lastFrame;
	int width, height;
	int cursorX, cursorY;
}EnguinApi_Canvas;

EnguinApi_Canvas EnguinApi_Canvas_Create(int,int);
void EnguinApi_Canvas_Write(EnguinApi_Canvas*, char*);
void EnguinApi_Canvas_Flush(EnguinApi_Canvas*);
void EnguinApi_Canvas_MoveTo(EnguinApi_Canvas*, int, int);
#endif
