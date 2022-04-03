#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<ncurses.h>

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

int ASH_UTILS_NumOfDigits(int n)
{
	int c = 0;
	while(n!=0){
		n/=10;
		c++;
	}
	return c;
}

void ASH_UTILS_AppendToString(char* str, char *buf, int len, int start)
{
	for(int i=0;i<len;i++){
		str[start+i] = buf[i];
	}
}

void ASH_UpdateSurface(ASH_Surface* s)
{
	int i;
	system("clear");

	// char* str = (char*)malloc(20*sizeof(char)*s->width*s->height+s->height);
	// int buf_size, buf_count = 0;

	// for(i=0;i<(s->width*s->height);i++){

	// 	(s->surface2+i)->ch = (s->surface1+i)->ch;
	// 	(s->surface2+i)->color.r = (s->surface1+i)->color.r;
	// 	(s->surface2+i)->color.g = (s->surface1+i)->color.g;
	// 	(s->surface2+i)->color.b = (s->surface1+i)->color.b;
	// 	(s->surface2+i)->color.type = (s->surface1+i)->color.type;

	// 	(s->surface1+i)->ch = ' ';
	// 	(s->surface1+i)->color.r = 25;
	// 	(s->surface1+i)->color.g = 25;
	// 	(s->surface1+i)->color.b = 25;
	// 	(s->surface1+i)->color.type = 0;

	// 	buf_size = 10+2+ASH_UTILS_NumOfDigits((s->surface2+i)->color.r)
	// 		+ASH_UTILS_NumOfDigits((s->surface2+i)->color.g)+ASH_UTILS_NumOfDigits((s->surface2+i)->color.b);
	// 	char buf[buf_size];
	// 	if((s->surface2+i)->color.type){
	// 		snprintf(buf, 20, "\x1b[38;2;%d;%d;%dm%c%c", (s->surface2+i)->color.r, (s->surface2+i)->color.g, 
	// 				(s->surface2+i)->color.b, (s->surface2+i)->ch, (s->surface2+i)->ch);
	// 	}
	// 	else{
	// 		snprintf(buf, 20, "\x1b[48;2;%d;%d;%dm%c%c", (s->surface2+i)->color.r, (s->surface2+i)->color.g, 
	// 				(s->surface2+i)->color.b, (s->surface2+i)->ch, (s->surface2+i)->ch);
	// 	}
	// 	ASH_UTILS_AppendToString(str,buf,buf_size,buf_count);
	// 	buf_count+=buf_size;
	// 	if((i+1)%s->width==0){
	// 		str[buf_count] = '\n';
	// 		buf_count+=1;
	// 	}
	// 	str[buf_count] = '\0';
	// }
	// printf("%s", str);
	// printf("\033[0m");

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

		if((s->surface2+i)->color.type){
			printf("\x1b[38;2;%d;%d;%dm%c%c", (s->surface2+i)->color.r, (s->surface2+i)->color.g, 
					(s->surface2+i)->color.b, (s->surface2+i)->ch, (s->surface2+i)->ch);
		}
		else{
			printf("\x1b[48;2;%d;%d;%dm%c%c", (s->surface2+i)->color.r, (s->surface2+i)->color.g, 
					(s->surface2+i)->color.b, (s->surface2+i)->ch, (s->surface2+i)->ch);
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


