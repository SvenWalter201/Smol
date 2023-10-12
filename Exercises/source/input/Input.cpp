#include "Input.h"
#include <conio.h>

bool InputHandler::GetKeyPressed(int key) const
{
	return (GetKeyState(key) & (1 << 15)); /*Check if high-order bit is set (1 << 15)*/
}

POINT InputHandler::GetMousePosition()
{
	POINT p;
	GetCursorPos(&p);
	return p;
}


