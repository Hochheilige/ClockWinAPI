#include "Window.h"

Window::Window() {
	GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &csbi);
	hWindow = GetConsoleWindow();
	hDeviceContext = GetDC(hWindow);
}

Window::~Window() {
	ReleaseDC(hWindow, hDeviceContext);
}
