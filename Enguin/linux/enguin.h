#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<ctype.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<fcntl.h>
#include<sys/time.h>

int ENGUIN_UTILS_CountDigits(int n)
{
	int c = 0;
	while(n!=0){
		n/=10;
		c++;
	}
	return c;
}

typedef struct{
	char ch;
	int modified;
	//int[3] color_f;
	//int[3] color_b;
}ENGUIN_Cell;

typedef struct{
	int size;
	int maxLength;
	char* string;
}ENGUIN_Buffer;

typedef struct{
	ENGUIN_Cell* cells;
	int width, height;
	int cursorX, cursorY;
	ENGUIN_Buffer lastFrame;
}ENGUIN_Surface;

ENGUIN_Buffer ENGUIN_BufferInit(int size, int maxLength)
{
	ENGUIN_Buffer buff;
	buff.size = size;
	buff.maxLength = maxLength;
	buff.string = (char*)malloc(size*maxLength*sizeof(char));
	for(int i=0;i<size;i++){
		*(buff.string+i*maxLength) = '\0';
	}
	return buff;
}

char* ENGUIN_BufferGet(ENGUIN_Buffer* buff, int id)
{
	return buff->string+id*buff->maxLength;
}

void ENGUIN_BufferSet(ENGUIN_Buffer* buff, int id, char* str)
{
	int i;
	if(strlen(str)<=buff->maxLength){
		for(i=0;i<buff->maxLength;i++){
			if(i<=strlen(str)){
				*(buff->string+id*buff->maxLength+i) = *(str+i);
			}
			else{
				*(buff->string+id*buff->maxLength+i) = ' ';
			}
		}
	}
}

char* ENGUIN_CellToString(ENGUIN_Surface* s, int id)
{
	int x = 2*(id%s->width)+1;
	int y = (id/s->width)+1;
	//"\033[y;xH%c%c"
	int len = strlen("\033[;HCC")+ENGUIN_UTILS_CountDigits(x)+ENGUIN_UTILS_CountDigits(y)+1;
	char* str = (char*)malloc(len*sizeof(char));
	snprintf(str, len, "\033[%d;%dH%c%c", y, x, s->cells[id].ch, s->cells[id].ch);
	return str;
}

void ENGUIN_Delay(float seconds)
{
	usleep((int)(seconds*1000000.0f));
}

void ENGUIN_StrongKill(int sig_num)
{
	system("reset");
	_exit(0);
}

void ENGUIN_KillSurface(ENGUIN_Surface* s)
{
	ENGUIN_StrongKill(0);
}

ENGUIN_Surface ENGUIN_CreateSurface(int w, int h)
{
	printf("\e[8;%d;%dt", h+1, w*2);
	system("tput civis");
	system("stty -echo");
	system("clear");
	signal(SIGINT, ENGUIN_StrongKill);

	ENGUIN_Surface s;
	s.width = w;
	s.height = h;
	s.cursorX = 0;
	s.cursorY = 0;
	s.cells = (ENGUIN_Cell*)malloc(w*h*sizeof(ENGUIN_Cell));
	s.lastFrame = ENGUIN_BufferInit(w*h, strlen("\033[;HCC")+ENGUIN_UTILS_CountDigits(w)+ENGUIN_UTILS_CountDigits(h)+1);

	for(int i=0;i<(w*h);i++){
		s.cells[i].ch = '.';
	}
	return s;
}

void ENGUIN_CursorMoveTo(ENGUIN_Surface* s, int x, int y)
{
	s->cursorX = x;
	s->cursorY = y;
	// x = 2*x+1;
	// y = y+1;
	// printf("\033[%d;%dH", y+1, 2*x+1);

	// int len = strlen("\033[;H")+ENGUIN_UTILS_CountDigits(x)+ENGUIN_UTILS_CountDigits(y)+1;
	// char str[len];
	// snprintf(str, len, "\033[%d;%dH", y, x);
	// ENGUIN_BufferAdd(&s->buffer, str);
}

void ENGUIN_CursorWrite(ENGUIN_Surface* s, char ch)
{
	// printf("%c%c",c,c);
	int x = s->cursorX;
	int y = s->cursorY;
	int id = y*s->width+x;
	
	if(x>=0&&x<s->width&&y>=0&&y<s->height){
		s->cells[id].ch = ch;
		s->cells[id].modified = 1;
	}

	// int len = 2*sizeof(char)+1;
	// char str[len];
	// snprintf(str, len, "%c%c", c, c);
	// ENGUIN_BufferAdd(&s->buffer, str);
}

// void ENGUIN_CursorSetColor(int type, int color[3])
// {
// 	if(type==0){
// 		printf("\033[48;2;%d;%d;%dm", color[0], color[1], color[2]);
// 	}
// 	if(type==1){
// 		printf("\033[38;2;%d;%d;%dm", color[0], color[1], color[2]);
// 	}
// }

void ENGUIN_DrawSurface(ENGUIN_Surface* s)
{
	printf("\033[1;1H");
	for(int i=0;i<s->height;i++){
		for(int j=0;j<s->width;j++){
			printf("%c%c", s->cells[i*s->width+j].ch, s->cells[i*s->width+j].ch);
		}
		printf("\n");
	}
}

void ENGUIN_UpdateSurface(ENGUIN_Surface* s)
{
	// int x,y;
	// char ch;

	// for(int i=0;i<(s->width*s->height);i++){
	// 	if(s->cells1[i].ch != s->cells2[i].ch){
	// 		s->cells1[i].ch = s->cells2[i].ch;
	// 		x = i%s->width;
	// 		y = i/s->width;
	// 		ch = s->cells1[i].ch;

	// 		ENGUIN_CursorMoveTo(s,x,y);
	// 		//ENGUIN_CursorSetColor(0, (int[]){5,20,50});
	// 		//ENGUIN_CursorSetColor(1, (int[]){245,125,233});
	// 		ENGUIN_CursorWrite(s,ch);
	// 	}

	// 	if(s->cells2[i].ch!='.'){
	// 		s->cells2[i].ch = '.';
	// 	}
	// }

	char* payload = (char*)malloc(s->width*s->height*(strlen("\033[;HCC")+ENGUIN_UTILS_CountDigits(s->width)+ENGUIN_UTILS_CountDigits(s->height))+1);
	char* cellStr = (char*)malloc(strlen("\033[;HCC")+ENGUIN_UTILS_CountDigits(s->width)+ENGUIN_UTILS_CountDigits(s->height)+1);

	for(int i=0;i<s->width*s->height;i++){
		if(s->cells[i].modified){
			s->cells[i].modified = 0;
			cellStr = ENGUIN_CellToString(s, i);
			if(!(strcmp(cellStr, ENGUIN_BufferGet(&s->lastFrame, i)))){
				ENGUIN_BufferSet(&s->lastFrame, i, cellStr);
				strcat(payload, cellStr);
			}
		}
	}

	// TODO -> Problem s payload
	// printf("%s ", payload);
	printf("%s", cellStr);
	fflush(stdout);

	free(payload);
	free(cellStr);
}

// void ENGUIN_DrawPoint(ENGUIN_Surface* s, int x, int y, char ch)
// {
// 	if(x>=0&&x<s->width&&y>=0&&y<s->height){
// 		// char str[3];
// 		// snprintf(str, 3, "%c%c", ch, ch);
// 		ENGUIN_CursorMoveTo(s, x, y);
// 		ENGUIN_CursorWrite(s, "DD");
// 	}
// }

