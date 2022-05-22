#include"canvas.h"

//Cell
void EnguinApi_Cell_SetForeground(EnguinApi_Cell* cell, int foreground[3])
{
	cell->foreground[0]=foreground[0];
	cell->foreground[1]=foreground[1];
	cell->foreground[2]=foreground[2];
}

void EnguinApi_Cell_ResetForeground(EnguinApi_Cell* cell)
{
	EnguinApi_Cell_SetForeground(cell, (int[3]){-1,-1,-1});
}

void EnguinApi_Cell_SetBackground(EnguinApi_Cell* cell, int background[3])
{
	cell->background[0]=background[0];
	cell->background[1]=background[1];
	cell->background[2]=background[2];
}

void EnguinApi_Cell_ResetBackground(EnguinApi_Cell* cell)
{
	EnguinApi_Cell_SetBackground(cell, (int[3]){-1,-1,-1});
}

EnguinApi_Cell EnguinApi_Cell_Create(char ch, int x, int y, int foreground[3], int background[3])
{
	EnguinApi_Cell cell = {.ch=ch, .x=x, .y=y, .isModified=1};
	EnguinApi_Cell_SetForeground(&cell, foreground);
	EnguinApi_Cell_SetBackground(&cell, background);
	return cell;
}

void EnguinApi_Cell_Reset(EnguinApi_Cell* cell)
{
	cell->ch = ' ';
	EnguinApi_Cell_ResetBackground(cell);
	EnguinApi_Cell_ResetForeground(cell);
	cell->isModified = 1;
}

char* EnguinApi_Cell_ToString(EnguinApi_Cell* cell)
{
	int len = strlen("\033[;HC")+EnguinApi_Utils_CountDigits(cell->x+1)+EnguinApi_Utils_CountDigits(cell->y+1)+
		strlen("\033[48;2;255;255;255m")+strlen("\033[38;2;255;255;255m")+1;
	char* str = (char*)malloc(len*sizeof(char));
	snprintf(str, len, "\033[%d;%dH\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm%c",cell->y+1,cell->x+1,
		cell->foreground[0], cell->foreground[1], cell->foreground[2], 
		cell->background[0], cell->background[1], cell->background[2], cell->ch);
	return str;
}

//Canvas
EnguinApi_Canvas EnguinApi_Canvas_Create(int width, int height)
{
	EnguinApi_Canvas canvas = {.width=width, .height=height, .cursorX=0, .cursorY=0};
	canvas.cells = (EnguinApi_Cell*)malloc(width*height*sizeof(EnguinApi_Cell));
	int maxLength = strlen("\033[;HC")+EnguinApi_Utils_CountDigits(width)+EnguinApi_Utils_CountDigits(height)+
		strlen("\033[48;2;255;255;255m")+strlen("\033[38;2;255;255;255m")+1;
	canvas.lastFrame = EnguinApi_Utils_Buffer_Create(width*height, maxLength);
	for(int i=0;i<width*height;i++){
		canvas.cells[i] = EnguinApi_Cell_Create(' ', i%width, i/width, (int[3]){-1,-1,-1}, (int[3]){-1,-1,-1});
	}
	return canvas;
}

void EnguinApi_Canvas_Write(EnguinApi_Canvas* canvas, char* str)
{
	int pointer;
	for(int i=0;i<(int)strlen(str);i++){
		pointer = canvas->cursorY*canvas->width+canvas->cursorX;
		if(canvas->cursorX>=0&&canvas->cursorX<canvas->width&&canvas->cursorY>=0&&canvas->cursorY<canvas->height){
			canvas->cells[pointer].ch = str[i];
			canvas->cells[pointer].x = canvas->cursorX;
			canvas->cells[pointer].y = canvas->cursorY;
			canvas->cells[pointer].isModified = 1;
		}
		canvas->cursorX+=1;
	}
}

void EnguinApi_Canvas_Flush(EnguinApi_Canvas* canvas)
{
	char* payload = (char*)malloc(canvas->width*canvas->height*(strlen("\033[;HC")+
		EnguinApi_Utils_CountDigits(canvas->width)+EnguinApi_Utils_CountDigits(canvas->height)+
		strlen("\033[48;2;255;255;255m")+strlen("\033[38;2;255;255;255m"))+1);
	payload[0] = '\0';
	char* cellStr;
	char* fromBuff;

	for(int i=0;i<canvas->width*canvas->height;i++){
		if(canvas->cells[i].isModified){
			canvas->cells[i].isModified = 0;
			cellStr = EnguinApi_Cell_ToString(&canvas->cells[i]);
			fromBuff = EnguinApi_Utils_Buffer_Get(&canvas->lastFrame, i);
			if((strcmp(cellStr, fromBuff))!=0){
				EnguinApi_Utils_Buffer_Set(&canvas->lastFrame, i, cellStr);
				strcat(payload, cellStr);
			}
			free(cellStr);
		}
	}
	printf("%s", payload);
	fflush(stdout);
	free(payload);
}

void EnguinApi_Canvas_MoveTo(EnguinApi_Canvas* canvas, int x, int y)
{
	canvas->cursorX = x;
	canvas->cursorY = y;
}
