#pragma once
#ifndef UTILS_H
#define UTILS_H

#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<signal.h>

int SRAND_CALL;

int EnguinApi_Utils_RandomNumber(int, int);
int EnguinApi_Utils_CountDigits(int);
void EnguinApi_Utils_Sleep(float);

typedef struct{
	int size;
	int maxLength;
	char* string;
}EnguinApi_Utils_Buffer;

EnguinApi_Utils_Buffer EnguinApi_Utils_Buffer_Create(int, int);
char* EnguinApi_Utils_Buffer_Get(EnguinApi_Utils_Buffer*, int);
void EnguinApi_Utils_Buffer_Set(EnguinApi_Utils_Buffer*, int, char*);
void EnguinApi_Utils_Kill();

#endif
