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
#ifndef TINYUI_WIDGETPAINTER_H_INCLUDED
#define TINYUI_WIDGETPAINTER_H_INCLUDED

namespace UI {

class Widget;

class WidgetPainter
{
protected:
	WidgetPainter(void) { }
public:
	virtual ~WidgetPainter(void) { }

	virtual void Create(Widget *w) = 0;
	virtual void Draw(Widget *w) = 0;
	virtual void Remove(Widget *w) = 0;
	virtual void Update(Widget *w) = 0;

	virtual void Release() = 0;
};

}
#endif
