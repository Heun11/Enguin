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
	EnguinApi_Cell_SetForeground(cell, cell->default_foreground);
}

void EnguinApi_Cell_SetBackground(EnguinApi_Cell* cell, int background[3])
{
	cell->background[0]=background[0];
	cell->background[1]=background[1];
	cell->background[2]=background[2];
}

void EnguinApi_Cell_ResetBackground(EnguinApi_Cell* cell)
{
	EnguinApi_Cell_SetBackground(cell, cell->default_background);
}

EnguinApi_Cell EnguinApi_Cell_Create(char ch, int x, int y, int wF, int wB, int foreground[3], int background[3])
{
	EnguinApi_Cell cell = {.ch=ch, .x=x, .y=y, .isModified=1, .wantBack=wB, .wantFore=wF, .default_ch=ch};
	cell.default_background[0] = background[0];
	cell.default_background[1] = background[1];
	cell.default_background[2] = background[2];
	cell.default_foreground[0] = foreground[0];
	cell.default_foreground[1] = foreground[1];
	cell.default_foreground[2] = foreground[2];
	EnguinApi_Cell_SetForeground(&cell, foreground);
	EnguinApi_Cell_SetBackground(&cell, background);
	return cell;
}

void EnguinApi_Cell_Reset(EnguinApi_Cell* cell)
{
	cell->ch = cell->default_ch;
	EnguinApi_Cell_ResetBackground(cell);
	EnguinApi_Cell_ResetForeground(cell);
	cell->isModified = 1;
}

char* EnguinApi_Cell_ToString(EnguinApi_Cell* cell)
{
	int len = strlen("\x1b[;HC")+EnguinApi_Utils_CountDigits(cell->x+1)+EnguinApi_Utils_CountDigits(cell->y+1)+
		strlen("\x1b[48;2;255;255;255m")+strlen("\x1b[38;2;255;255;255m")+1;
	char* str = (char*)malloc(len*sizeof(char));
	if(cell->wantFore&&cell->wantBack){
		snprintf(str, len, "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm\x1b[48;2;%d;%d;%dm%c",cell->y+1,cell->x+1,
			cell->foreground[0], cell->foreground[1], cell->foreground[2], 
			cell->background[0], cell->background[1], cell->background[2], cell->ch);
	}
	else if(cell->wantFore){
		snprintf(str, len, "\x1b[%d;%dH\x1b[38;2;%d;%d;%dm%c",cell->y+1,cell->x+1,
			cell->foreground[0], cell->foreground[1], cell->foreground[2], cell->ch);
	}
	else if(cell->wantBack){
		snprintf(str, len, "\x1b[%d;%dH\x1b[48;2;%d;%d;%dm%c",cell->y+1,cell->x+1,
			cell->background[0], cell->background[1], cell->background[2], cell->ch);
	}
	else{
		snprintf(str, len, "\x1b[%d;%dH%c", cell->y+1, cell->x+1, cell->ch);
	}
	return str;
}

//Canvas
void EnguinApi_Canvas_SetForeground(EnguinApi_Canvas* canvas, int foreground[3])
{
	canvas->foreground[0]=foreground[0];
	canvas->foreground[1]=foreground[1];
	canvas->foreground[2]=foreground[2];
}

void EnguinApi_Canvas_SetBackground(EnguinApi_Canvas* canvas, int background[3])
{
	canvas->background[0]=background[0];
	canvas->background[1]=background[1];
	canvas->background[2]=background[2];
}

EnguinApi_Canvas EnguinApi_Canvas_Create(int width, int height, int wF, int wB, int default_bck[3], int default_frnt[3], char default_ch)
{
	EnguinApi_Canvas canvas = {.width=width, .height=height, .cursorX=0, .cursorY=0, .wantFore=wF, .wantBack=wB, .default_ch=default_ch};
	canvas.default_background[0] = default_bck[0];
	canvas.default_background[1] = default_bck[1];
	canvas.default_background[2] = default_bck[2];
	canvas.default_foreground[0] = default_frnt[0];
	canvas.default_foreground[1] = default_frnt[1];
	canvas.default_foreground[2] = default_frnt[2];
	EnguinApi_Canvas_SetForeground(&canvas, canvas.default_background);
	EnguinApi_Canvas_SetBackground(&canvas, canvas.default_foreground);
	canvas.cells = (EnguinApi_Cell*)malloc(width*height*sizeof(EnguinApi_Cell));
	int maxLength = strlen("\x1b[;HC")+EnguinApi_Utils_CountDigits(width)+EnguinApi_Utils_CountDigits(height)+
		strlen("\x1b[48;2;255;255;255m")+strlen("\x1b[48;2;255;255;255m")+1;
	// if(canvas.wantBack){
	// 	maxLength+=strlen("\x1b[48;2;255;255;255m");
	// }
	// if(canvas.wantFore){
	// 	maxLength+=strlen("\x1b[48;2;255;255;255m");
	// }
	canvas.lastFrame = EnguinApi_Utils_Buffer_Create(width*height, maxLength);
	for(int i=0;i<width*height;i++){
		canvas.cells[i] = EnguinApi_Cell_Create(canvas.default_ch, i%width, i/width, canvas.wantFore, canvas.wantBack, canvas.foreground, canvas.background);
	}
	return canvas;
}

void EnguinApi_Canvas_Write(EnguinApi_Canvas* canvas, char* str, int foreground[3], int background[3])
{
	int pointer;
	for(int i=0;i<(int)strlen(str);i++){
		pointer = canvas->cursorY*canvas->width+canvas->cursorX;
		if(canvas->cursorX>=0&&canvas->cursorX<canvas->width&&canvas->cursorY>=0&&canvas->cursorY<canvas->height){
			canvas->cells[pointer].ch = str[i];
			canvas->cells[pointer].x = canvas->cursorX;
			canvas->cells[pointer].y = canvas->cursorY;
			// EnguinApi_Cell_SetForeground(&canvas->cells[pointer], canvas->foreground);
			// EnguinApi_Cell_SetBackground(&canvas->cells[pointer], canvas->background);
			EnguinApi_Cell_SetForeground(&canvas->cells[pointer], foreground);
			EnguinApi_Cell_SetBackground(&canvas->cells[pointer], background);
			canvas->cells[pointer].isModified = 1;
		}
		canvas->cursorX+=1;
	}
}

void EnguinApi_Canvas_Flush(EnguinApi_Canvas* canvas)
{
	char* payload = (char*)malloc(canvas->width*canvas->height*(strlen("\x1b[;HC")+
		EnguinApi_Utils_CountDigits(canvas->width)+EnguinApi_Utils_CountDigits(canvas->height)+
		strlen("\x1b[48;2;255;255;255m")+strlen("\x1b[38;2;255;255;255m"))+1);
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

void EnguinApi_Canvas_Erease(EnguinApi_Canvas* canvas, int x1, int y1, int x2, int y2)
{
	for(int y=y1;y<=y2;y++){
		for(int x=x1;x<=x2;x++){
			EnguinApi_Cell_Reset(&canvas->cells[y*canvas->width+x]);
		}
	}
}

void EnguinApi_Canvas_CursorHide()
{
	system("tput civis");
}

void EnguinApi_Canvas_CursorShow()
{
	system("tput cnorm");
}

void EnguinApi_Canvas_InputHide()
{
	system("stty -echo");
}

void EnguinApi_Canvas_InputShow()
{
	system("stty echo");
}
