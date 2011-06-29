
#include "Form.h"
#include "Button.h"
#include "Static.h"
#include "TextField.h"
#include "Win32Window.h"

class SimpleDelegate : public UI::Delegate {
	UI::Win32Window *mainwindow_;
public:
	SimpleDelegate(UI::Win32Window *w) : mainwindow_(w) { }
	void Invoke(UI::EventType e) {
		if (e == UI::Clicked) mainwindow_->ExitEventLoop();
	}
};

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	UI::Win32Window window(hInstance,640,480,std::string("TestWindow"));

	UI::Form form(&window);
	UI::Button button1("Button1",10,10,100,30);
	UI::Static label1("Label1",10,50,100,20);
	UI::TextField text1;

	text1.Position(110,50);
	text1.Size(100,20);
	
	form.Add(&button1);
	form.Add(&label1);
	form.Add(&text1);
	form.Draw();
	text1.Text("Edit this!");

	SimpleDelegate d(&window);
	button1.Delegate(&d);
	return window.EventLoop();
}

