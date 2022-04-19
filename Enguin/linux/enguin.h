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

typedef struct{
	char ch;
	//int[3] color_f;
	//int[3] color_b;
}ENGUIN_Cell;

typedef struct{
	ENGUIN_Cell* cells1;
	ENGUIN_Cell* cells2;
	int width, height;
}ENGUIN_Surface;

void ENGUIN_StrongKill(int sig_num)
{
	system("reset");
	exit(0);
}

void ENGUIN_KillSurface(ENGUIN_Surface* s)
{
	free(s->cells1);
	free(s->cells2);
	s->cells1 = NULL;
	s->cells2 = NULL;
	s->width = 0;
	s->height = 0;
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
	s.cells1 = (ENGUIN_Cell*)malloc(w*h*sizeof(ENGUIN_Cell));
	s.cells2 = (ENGUIN_Cell*)malloc(w*h*sizeof(ENGUIN_Cell));

	for(int i=0;i<(w*h);i++){
		s.cells1[i].ch = 'c';
		s.cells2[i].ch = 'c';
	}
	return s;
}

void ENGUIN_DrawSurface(ENGUIN_Surface* s)
{
	printf("\033[u");
	for(int i=0;i<s->height;i++){
		for(int j=0;j<s->width;j++){
			printf("%c%c", s->cells1[i*s->width+j].ch, s->cells1[i*s->width+j].ch);
		}
		printf("\n");
	}
}

