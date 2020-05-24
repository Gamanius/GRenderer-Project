#include "../GRenderer.h"
#undef UNICODE
#include <Windows.h>
#include <gl/GL.h>
#include <wglext.h>

//WinAPI specific varibles
HINSTANCE hInstance;

void GWindow::Window::init() {
	//TODO Load functions with getprocadress and do some attrib stuff
}

GWindow::Window::Window(std::string name, GGeneral::Point<int> pos, GGeneral::Dimension<int> dim) {}