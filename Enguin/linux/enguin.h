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

void ENGUIN_Delay(float seconds)
{
	fflush(stdout);
	usleep((int)(seconds*1000000.0f));
}

void ENGUIN_StrongKill(int sig_num)
{
	system("reset");
	_exit(0);
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
		s.cells1[i].ch = '.';
		s.cells2[i].ch = '.';
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

void ENGUIN_UpdateSurface(ENGUIN_Surface* s)
{
	int x,y;
	char ch;
	for(int i=0;i<(s->width*s->height);i++){
		if(s->cells1[i].ch != s->cells2[i].ch){
			s->cells1[i].ch = s->cells2[i].ch;
			//s->cells2[i].ch = '.';
			x = i%s->width;
			y = i/s->width;
			ch = s->cells1[i].ch;
			printf("\033[%d;%dH%c%c", y+1, 2*x+1, ch, ch);
		}
	}
}

void ENGUIN_DrawPoint(ENGUIN_Surface* s, int x, int y, char ch)
{
	if(x>=0&&x<s->width&&y>=0&&y<s->height && s->cells1[y*s->width+x].ch!=ch){
		printf("\033[%d;%dH%c%c", y+1, 2*x+1, ch, ch);
		s->cells2[y*s->width+x].ch = ch;
	}
}

