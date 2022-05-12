#include"canvas.h"

//TODO->Everithing around canvas (canvas, cell,...)

EnguinApi_Canvas EnguinApi_CreateCanvas(int width, int height)
{
	EnguinApi_Canvas canvas = {.width=width,.height=height};
	return canvas;
}
