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
#ifndef TINYUI_WIN32WINDOW_H_INCLUDED
#define TINYUI_WIN32WINDOW_H_INCLUDED

#include <string>
#include <Window.h>
#include <Windows.h>
#include "Win32Painter.h"

namespace UI {

const static char *className = "TinyUI";

class Win32Window : public Window
{
	HINSTANCE hInst_;
	HWND hwnd_;
	ATOM windowClass_;
	Win32Painter painter_;
	std::string title_;
	bool runEventLoop_;
public:
	Win32Window(HINSTANCE hInst,int width, int height, std::string &title = std::string("TinyUI Window"));
	~Win32Window(void);
	WidgetPainter *Painter() { return new Win32Painter(hwnd_); }
	int EventLoop();
	void ExitEventLoop() { runEventLoop_ = false; }
};

}
#endif
