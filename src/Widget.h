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
#ifndef TINYUI_WIDGET_H_INCLUDED
#define TINYUI_WIDGET_H_INCLUDED

#include <stdio.h>
#include "Event.h"

namespace UI {

	class WidgetPainter;

	class Widget {
		unsigned int x_,y_;
		unsigned int width_,height_;
		WidgetPainter *painter_;
		Delegate *delegate_;
	public:
		Widget();
		Widget(int x, int y, int w, int h) : x_(x),y_(y),width_(w),height_(h),painter_(NULL),delegate_(NULL) { }
		virtual ~Widget();
		void Position(unsigned int x, unsigned int y) { x_ = x; y_ = y; }
		void Size(unsigned int w,unsigned int h) { width_ = w; height_ = h; }
		unsigned int X() const { return x_; }
		unsigned int Y() const { return y_; }
		unsigned int Width() const { return width_; }
		unsigned int Height() const { return height_; }
		void Painter(WidgetPainter *w) { painter_ = w; }
		WidgetPainter *Painter() const { return painter_; }
		void Draw();
		void Create();
		void Delegate(Delegate *d) { delegate_ = d; }
		// events
		virtual void OnTextChange();
		virtual void OnClicked();
		virtual void OnFocus();
	};



}
#endif
