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

#include "Win32Painter.h"
#include "Button.h"
#include "Static.h"
#include "TextField.h"

namespace UI {

LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

Win32Painter::Win32Painter(void) : hwnd_(NULL)
{
}


Win32Painter::~Win32Painter(void)
{
	if (hwnd_) {
		SetWindowLong(hwnd_, GWL_WNDPROC, (LONG)originalWndProc_);	
		DestroyWindow(hwnd_);
	}
}


void Win32Painter::Draw(Widget *w)
{

}

void Win32Painter::Create(Widget *w)
{
	Button *button;
	Static *label;
	TextField *textField;

	HINSTANCE inst = (HINSTANCE)GetWindowLong(parent_, GWL_HINSTANCE);
	if ((button=dynamic_cast<Button*>(w))) {
		hwnd_ = CreateWindow("BUTTON",button->Label().c_str(),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,button->X(),button->Y(),button->Width(),button->Height(),parent_,NULL,inst,NULL);
	} else if ((label=dynamic_cast<Static*>(w))) {
		hwnd_ = CreateWindow("STATIC",label->Label().c_str(),WS_CHILD|WS_VISIBLE|SS_LEFT,label->X(),label->Y(),label->Width(),label->Height(),parent_,NULL,inst,NULL);
	} else if ((textField=dynamic_cast<TextField*>(w))) {
		hwnd_ = CreateWindow("EDIT",textField->Text().c_str(),WS_CHILD|WS_VISIBLE|ES_LEFT|ES_AUTOHSCROLL|WS_BORDER,textField->X(),textField->Y(),textField->Width(),textField->Height(),parent_,NULL,inst,NULL);
	}
	originalWndProc_ = (WNDPROC)SetWindowLong(hwnd_, GWL_WNDPROC, (LONG)WndProc);	
	SetWindowLong(hwnd_, GWL_USERDATA, (LONG)w);
}

void Win32Painter::Update(Widget *w)
{
	Button *button;
	if ((button=reinterpret_cast<Button*>(w))) {
		SetWindowPos(hwnd_,NULL,w->X(),w->Y(),w->Width(),w->Height(),0);
		SetWindowText(hwnd_,button->Label().c_str());
	}
}

void Win32Painter::Remove(Widget *w)
{
	if (hwnd_) {
		SetWindowLong(hwnd_, GWL_WNDPROC, (LONG)originalWndProc_);	
		DestroyWindow(hwnd_);
	}
}

}
