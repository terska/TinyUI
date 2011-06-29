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

#include "Widget.h"
#include "WidgetPainter.h"

namespace UI {

Widget::Widget(void)
	: painter_(NULL)
	, x_(0)
	, y_(0)
	, width_(10)
	, height_(10)
	, delegate_(NULL)
{
}


Widget::~Widget(void)
{
	painter_->Release();
}


void Widget::Draw()
{
	painter_->Draw(this);
}

void Widget::Create()
{
	painter_->Create(this);
}

void Widget::OnClicked()
{
	if (delegate_) {
		delegate_->Invoke(Clicked);
	}
	// else do nothing
}

void Widget::OnTextChange()
{
	if (delegate_) {
		delegate_->Invoke(TextChanged);
	}
	// else do nothing
}

void Widget::OnFocus()
{
	if (delegate_) {
		delegate_->Invoke(FocusIn);
	}
	// else do nothing
}

}
