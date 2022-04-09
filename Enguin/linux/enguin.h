#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>

typedef struct{
	int r,g,b;
}ENGUIN_Color;

typedef struct{
	char ch;
	ENGUIN_Color back_c;
	ENGUIN_Color front_c;
}ENGUIN_Char;

typedef struct{
	int width;
	int height;

	char ch;
	ENGUIN_Color back_c;
	ENGUIN_Color front_c;

	ENGUIN_Char* surface1;
	ENGUIN_Char* surface2;
}ENGUIN_Surface;

void ENGUIN_StrongKill(int sig_num)
{
    signal(SIGINT, ENGUIN_StrongKill);
	system("tput cnorm");
	system("clear");
    exit(0);
    fflush(stdout);
}

void ENGUIN_KillSurface(ENGUIN_Surface* s)
{
	free(s->surface1);
	free(s->surface2);
	s->surface1 = NULL;
	s->surface2 = NULL;
	s->width = 0;
	s->height = 0;
	system("tput cnorm");
}

ENGUIN_Surface ENGUIN_CreateSurface(int s_w, int s_h, char c, ENGUIN_Color* back_c, ENGUIN_Color* front_c)
{
	printf("\e[8;%d;%dt", s_h+2, s_w*2);
	system("tput civis");
	system("clear");
	signal(SIGINT, ENGUIN_StrongKill);
	ENGUIN_Surface s;
	s.width = s_w;
	s.height = s_h;
	s.surface1 = (ENGUIN_Char*)malloc(s_w*s_h*sizeof(ENGUIN_Char));
	s.surface2 = (ENGUIN_Char*)malloc(s_w*s_h*sizeof(ENGUIN_Char));
	for(int i=0;i<(s_w*s_h);i++){
		s.surface1[i].ch = c;
		s.surface1[i].back_c.r = back_c->r;
		s.surface1[i].back_c.g = back_c->g;
		s.surface1[i].back_c.b = back_c->b;

		s.surface1[i].front_c.r = front_c->r;
		s.surface1[i].front_c.g = front_c->g;
		s.surface1[i].front_c.b = front_c->b;

		s.ch = c;
		s.back_c.r = back_c->r;
		s.back_c.g = back_c->g;
		s.back_c.b = back_c->b;

		s.front_c.r = front_c->r;
		s.front_c.g = front_c->g;
		s.front_c.b = front_c->b;
	}
	return s;
}

void ENGUIN_Delay(float seconds)
{
	usleep((int)(seconds*1000000.0f));
}

int ENGUIN_UTILS_CountDigits(int n)
{
	int c = 0;
	while(n!=0){
		n/=10;
		c++;
	}
	return c;
}

void ENGUIN_UpdateSurface(ENGUIN_Surface* s)
{
	int i;
	system("echo \"\x1B[0;0H\"");
	char* str = (char*)malloc(1+(44)*sizeof(char)*s->width*s->height+s->height);
	strcpy(str, "");
	int buf_size;

	for(i=0;i<(s->width*s->height);i++){
		(s->surface2+i)->ch = (s->surface1+i)->ch;
		(s->surface2+i)->back_c.r = (s->surface1+i)->back_c.r;
		(s->surface2+i)->back_c.g = (s->surface1+i)->back_c.g;
		(s->surface2+i)->back_c.b = (s->surface1+i)->back_c.b;
		(s->surface2+i)->front_c.r = (s->surface1+i)->front_c.r;
		(s->surface2+i)->front_c.g = (s->surface1+i)->front_c.g;
		(s->surface2+i)->front_c.b = (s->surface1+i)->front_c.b;

		(s->surface1+i)->ch = s->ch;
		(s->surface1+i)->back_c.r = s->back_c.r;
		(s->surface1+i)->back_c.g = s->back_c.g;
		(s->surface1+i)->back_c.b = s->back_c.b;
		(s->surface1+i)->front_c.r = s->front_c.r;
		(s->surface1+i)->front_c.g = s->front_c.g;
		(s->surface1+i)->front_c.b = s->front_c.b;

		buf_size = 24+2+1+ENGUIN_UTILS_CountDigits((s->surface2+i)->back_c.r)
						+ENGUIN_UTILS_CountDigits((s->surface2+i)->back_c.g)
						+ENGUIN_UTILS_CountDigits((s->surface2+i)->back_c.b)
						+ENGUIN_UTILS_CountDigits((s->surface2+i)->front_c.r)
						+ENGUIN_UTILS_CountDigits((s->surface2+i)->front_c.g)
						+ENGUIN_UTILS_CountDigits((s->surface2+i)->front_c.b);

		char* buf = (char*)malloc(buf_size);
		snprintf(buf,44,"\x1b[48;2;%d;%d;%dm\x1b[38;2;%d;%d;%dm%c%c\033[0m", 
				(s->surface2+i)->back_c.r, (s->surface2+i)->back_c.g, (s->surface2+i)->back_c.b,
				(s->surface2+i)->front_c.r, (s->surface2+i)->front_c.g, (s->surface2+i)->front_c.b, 
				(s->surface2+i)->ch, (s->surface2+i)->ch);

		strcat(str, buf);
		free(buf);
		if((i+1)%s->width==0){
			strcat(str, "\n");
		}
	}
	printf("%s", str);
	free(str);
	str = NULL;
}

void ENGUIN_DrawPoint(ENGUIN_Surface* s, char c, int x, int y, ENGUIN_Color* back_c, ENGUIN_Color* front_c)
{
	if(x<s->width && y<s->height && x>=0 && y>=0){
		(s->surface1+y*s->width+x)->ch = c;
		(s->surface1+y*s->width+x)->back_c.r = back_c->r;
		(s->surface1+y*s->width+x)->back_c.g = back_c->g;
		(s->surface1+y*s->width+x)->back_c.b = back_c->b;

		(s->surface1+y*s->width+x)->front_c.r = front_c->r;
		(s->surface1+y*s->width+x)->front_c.g = front_c->g;
		(s->surface1+y*s->width+x)->front_c.b = front_c->b;
	}
}

