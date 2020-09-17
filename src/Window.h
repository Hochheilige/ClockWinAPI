#pragma once

#include <Windows.h>

struct Window {
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND hWindow;
	HDC hDeviceContext;

	Window();
	~Window();
};