#pragma once
#ifndef CANVAS_H
#define CANVAS_H
#include"utils.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

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
#endif
