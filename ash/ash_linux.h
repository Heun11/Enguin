#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct{
	int r,g,b;
	int type;
}ASH_Color;

typedef struct{
	char ch;
	ASH_Color color;
}ASH_Char;

typedef struct{
	int width;
	int height;
	ASH_Char* surface1;
	ASH_Char* surface2;
}ASH_Surface;

ASH_Surface ASH_CreateSurface(int s_w, int s_h)
{
	printf("\e[8;%d;%dt", s_h+1, s_w*2);
	ASH_Surface s;
	s.width = s_w;
	s.height = s_h;
	s.surface1 = (ASH_Char*)malloc(s_w*s_h*sizeof(ASH_Char));
	s.surface2 = (ASH_Char*)malloc(s_w*s_h*sizeof(ASH_Char));
	for(int i=0;i<(s_w*s_h);i++){
		s.surface1[i].ch = ' ';
		s.surface1[i].color.r = 25;
		s.surface1[i].color.g = 25;
		s.surface1[i].color.b = 25;
		s.surface1[i].color.type = 0;
	}
	return s;
}

void ASH_KillSurface(ASH_Surface* s)
{
	free(s->surface1);
	free(s->surface2);
	s->surface1 = NULL;
	s->surface2 = NULL;
	s->width = 0;
	s->height = 0;
}

void ASH_Delay(float seconds)
{
	usleep((int)(seconds*1000000.0f));
}

void ASH_UpdateSurface(ASH_Surface* s)
{
	int i,j;
	system("clear");
	ASH_Char c;

	// for(i=0;i<s->height;i++){
	// 	for(j=0;j<s->width;j++){
	// 		(s->surface2+i*s->width+j)->ch = (s->surface1+i*s->width+j)->ch;
	// 		(s->surface2+i*s->width+j)->color.r = (s->surface1+i*s->width+j)->color.r;
	// 		(s->surface2+i*s->width+j)->color.g = (s->surface1+i*s->width+j)->color.g;
	// 		(s->surface2+i*s->width+j)->color.b = (s->surface1+i*s->width+j)->color.b;
	// 		(s->surface2+i*s->width+j)->color.type = (s->surface1+i*s->width+j)->color.type;
			
	// 		(s->surface1+i*s->width+j)->ch = ' ';
	// 		(s->surface1+i*s->width+j)->color.r = 25;
	// 		(s->surface1+i*s->width+j)->color.g = 25;
	// 		(s->surface1+i*s->width+j)->color.b = 25;
	// 		(s->surface1+i*s->width+j)->color.type = 0;
			

	// 		c.ch = (s->surface2+i*s->width+j)->ch;
	// 		c.color.r = (s->surface2+i*s->width+j)->color.r;
	// 		c.color.g = (s->surface2+i*s->width+j)->color.g;
	// 		c.color.b = (s->surface2+i*s->width+j)->color.b;
	// 		c.color.type = (s->surface2+i*s->width+j)->color.type;
	// 		if(c.color.type){
	// 			printf("\x1b[38;2;%d;%d;%dm%c%c", c.color.r, c.color.g, c.color.b, c.ch, c.ch);
	// 		}
	// 		else{
	// 			printf("\x1b[48;2;%d;%d;%dm%c%c", c.color.r, c.color.g, c.color.b, c.ch, c.ch);
	// 		}
	// 		printf("\033[0m");
	// 	}
	// 	printf("\n");
	// }
	for(i=0;i<(s->width*s->height);i++){
		(s->surface2+i)->ch = (s->surface1+i)->ch;
		(s->surface2+i)->color.r = (s->surface1+i)->color.r;
		(s->surface2+i)->color.g = (s->surface1+i)->color.g;
		(s->surface2+i)->color.b = (s->surface1+i)->color.b;
		(s->surface2+i)->color.type = (s->surface1+i)->color.type;

		(s->surface1+i)->ch = ' ';
		(s->surface1+i)->color.r = 25;
		(s->surface1+i)->color.g = 25;
		(s->surface1+i)->color.b = 25;
		(s->surface1+i)->color.type = 0;

		c.ch = (s->surface2+i)->ch;
		c.color.r = (s->surface2+i)->color.r;
		c.color.g = (s->surface2+i)->color.g;
		c.color.b = (s->surface2+i)->color.b;
		c.color.type = (s->surface2+i)->color.type;
		if(c.color.type){
			printf("\x1b[38;2;%d;%d;%dm%c%c", c.color.r, c.color.g, c.color.b, c.ch, c.ch);
		}
		else{
			printf("\x1b[48;2;%d;%d;%dm%c%c", c.color.r, c.color.g, c.color.b, c.ch, c.ch);
		}
		printf("\033[0m");
		
		if((i+1)%s->width==0){
			printf("\n");
		}
	}
}

void ASH_DrawPoint(ASH_Surface* s, char c, int x, int y, int r, int g, int b, int type)
{
	if(x<s->width && y<s->height){
		(s->surface1+y*s->width+x)->ch = c;
		(s->surface1+y*s->width+x)->color.r = r;
		(s->surface1+y*s->width+x)->color.g = g;
		(s->surface1+y*s->width+x)->color.b = b;
		(s->surface1+y*s->width+x)->color.type = type;
	}
}


