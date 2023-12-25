#pragma once
#include<windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp);
bool quit();
bool escKeyPressed();
void closeWindow();
void createWindow(const char* appName, int windowWidth, int windowHeight);