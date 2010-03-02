#include <windows.h>
#include <stdlib.h>

#include "pyramid.h"
using namespace D3D;
using namespace MyPyramid;

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

Pyramid pyramid;
const int WIDTH = 700;
const int HEIGHT = 700;
const float delta = 1.0f;
const unsigned TIME_VALUE_INDEX = 12;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR, int )
{
	HANDLE ghInstance;
	WNDCLASS wcex;
	HWND hwnd;
	TCHAR WindowTitle[] = _T("Cube");
    TCHAR WindowClassName[] = _T("AppClass");
	if (!hPrevInstance)
	{
		wcex.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.lpszClassName = WindowClassName;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName = 0;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;

		if (!RegisterClass(&wcex))
			return 0;
	}

	ghInstance = hInstance;
	hwnd = CreateWindow(WindowClassName, WindowTitle, 
		WS_CAPTION | WS_SYSMENU,			
		CW_USEDEFAULT, 0, WIDTH, HEIGHT, 
		NULL, NULL, hInstance, NULL);
	if (!hwnd)
	{
		return 0;
	}
	//SetClassLong(hwnd, TIME_VALUE_INDEX, 0);
	//SetTimer(hwnd, 0, 50, NULL);

	if (SUCCEEDED(pyramid.device.InitialDirect3D(hwnd)))
	{
		if (SUCCEEDED(pyramid.InitialObject()))
		{
			if (SUCCEEDED(pyramid.device.shader.InitialShader()))
			 {	   
				ShowWindow(hwnd, SW_SHOWDEFAULT);
				UpdateWindow(hwnd);
				MSG msg;
				ZeroMemory(&msg, sizeof(msg));
				while (msg.message!=WM_QUIT)
				{
					if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
					 else
					{
						//pyramid.time = GetClassLong(hwnd, TIME_VALUE_INDEX);
						pyramid.Draw(pyramid.PyramidVertex);
						
					}
				}
			}
		}
	}
	return 0;
}

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			pyramid.Move(-delta, TETHA);
			break;
		case VK_DOWN:
			pyramid.Move(delta, TETHA);
			break;
		case VK_LEFT:
			pyramid.Move(delta, PHI);
			break;
		case VK_RIGHT:
			pyramid.Move(-delta, PHI);
			break;
		} 
		break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
