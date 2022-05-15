#include"canvas.h"
//TODO->Everithing around canvas (canvas, cell,...)

EnguinApi_Cell EnguinApi_Cell_Create(char ch, int x, int y)
{
	EnguinApi_Cell cell = {.ch=ch, .x=x, .y=y};
	return cell;
}

void EnguinApi_Cell_Reset(EnguinApi_Cell* cell)
{
	cell->ch = ' ';
	cell->isModified = 1;
}

char* EnguinApi_Cell_ToString(EnguinApi_Cell* cell)
{
	int len = strlen("\033[;HCC")+EnguinApi_Utils_CountDigits(cell->x)+EnguinApi_Utils_CountDigits(cell->y)+1;
	char* str = (char*)malloc(len*sizeof(char));
	snprintf(str, len, "\033[%d;%dH%c%c",cell->y+1,2*cell->x+1,cell->ch,cell->ch);
	return str;
}
