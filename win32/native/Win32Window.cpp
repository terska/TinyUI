/*
  TinyUI -- Tiny User Interface Library

  Copyright (C) 2011 Anemic Software

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#include "Win32Window.h"
#include "Widget.h"

namespace UI {

	LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

	Win32Window::Win32Window(HINSTANCE hInst,int width, int height, std::string &title) 
		: hInst_(hInst)
		, title_(title)
	{
		WNDCLASS info;
		if (!GetClassInfo(hInst,className,&info)) {
			WNDCLASSEX wcex;

			wcex.cbSize = sizeof(WNDCLASSEX);

			wcex.style			= CS_HREDRAW | CS_VREDRAW;
			wcex.lpfnWndProc	= WndProc;
			wcex.cbClsExtra		= 0;
			wcex.cbWndExtra		= 0;
			wcex.hInstance		= hInst_;
			wcex.hIcon			= NULL; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUITEST));
			wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
			wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
			wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_GUITEST);
			wcex.lpszClassName	= className;
			wcex.hIconSm		= NULL; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

			windowClass_ = RegisterClassEx(&wcex);
		}
		hwnd_ = CreateWindow(className, 
			title_.c_str(), 
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
			NULL, 
			NULL, 
			hInst_, 
			NULL);

		ShowWindow(hwnd_,1);
		UpdateWindow(hwnd_);
	}


	Win32Window::~Win32Window(void)
	{
		DestroyWindow(hwnd_);
		// do not unregister class as there may be other windows still open
		//UnregisterClass(className,hInst_);
	}

	int Win32Window::EventLoop()
	{
		MSG msg;
		runEventLoop_ = true;
		while ((GetMessage(&msg, NULL, 0, 0)) && runEventLoop_)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		return (int)msg.wParam;
	}

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		char currentClassName[32];
		Window *window = NULL;
		Widget *widget = NULL;
		if (GetClassName(hWnd,currentClassName,32)) {
			if (strcmp(className,currentClassName) == 0) {
				window = (Window*)GetWindowLong(hWnd,GWL_USERDATA);
			} else {
				widget = (Widget*)GetWindowLong(hWnd,GWL_USERDATA);
			}
		} else {
			widget = (Widget*)GetWindowLong(hWnd,GWL_USERDATA);
		}
		switch (message)
		{
		case WM_COMMAND:
			switch (HIWORD(wParam)) {
			case BN_CLICKED:
				widget = (Widget*)GetWindowLong((HWND)lParam,GWL_USERDATA);
				if (widget) widget->OnClicked();
				break;
			case EN_CHANGE:
				if (widget) widget->OnTextChange();
				break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			if (widget) {
				UI::Win32Painter *p = dynamic_cast<UI::Win32Painter*>(widget->Painter());
				return CallWindowProc(p->OriginalWndProc(),hWnd,message,wParam,lParam);
			} else {
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		return 0;
	}

}
