#pragma once
#include <thread>
#include <windows.h>

class InputHandler
{
public:
	InputHandler(){}

	void StartHandlingInput();
	void StopHandlingInput();
	void HandleInputs();
	void GetChar();
	bool GetKeyPressed(int key) const;
	POINT GetMousePosition();
};