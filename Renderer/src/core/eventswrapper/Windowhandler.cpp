#pragma once
#include "GRenderer.h"
#include <Windows.h>
//This is because ID:0 should not be a valid id and is reserved
#define THIS_INSTANCE allWrapper[this->ID - 1]

static int getWindowsVirtualKeyCode(GWindow::VK key) {
	switch (key) {
	case GWindow::VK::LEFT_MB:		       return VK_LBUTTON;
	case GWindow::VK::RIGHT_MB:		       return VK_RBUTTON;
	case GWindow::VK::CANCEL:		       return VK_CANCEL;
	case GWindow::VK::MIDDLE_MB:	       return VK_MBUTTON;
	case GWindow::VK::X1_MB:		       return VK_XBUTTON1;
	case GWindow::VK::X2_MB:		       return VK_XBUTTON2;
	case GWindow::VK::LEFT_SHIFT:	       return VK_LSHIFT;
	case GWindow::VK::RIGHT_SHIFT:	       return VK_RSHIFT;
	case GWindow::VK::LEFT_CONTROL:	       return VK_LCONTROL;
	case GWindow::VK::RIGHT_CONTROL:       return VK_RCONTROL;
	case GWindow::VK::BACKSPACE:	       return VK_BACK;
	case GWindow::VK::TAB:			       return VK_TAB;
	case GWindow::VK::ENTER:	           return VK_RETURN;
	case GWindow::VK::ALT:			       return VK_MENU;
	case GWindow::VK::PAUSE:    	       return VK_PAUSE;
	case GWindow::VK::CAPSLOCK:		       return VK_CAPITAL;
	case GWindow::VK::ESCAPE:		       return VK_ESCAPE;
	case GWindow::VK::SPACE:		       return VK_SPACE;
	case GWindow::VK::PAGE_UP:		       return VK_PRIOR;
	case GWindow::VK::PAGE_DOWN:	       return VK_NEXT;
	case GWindow::VK::END:			       return VK_END;
	case GWindow::VK::HOME:			       return VK_HOME;
	case GWindow::VK::LEFTARROW:	       return VK_LEFT;
	case GWindow::VK::UPARROW:		       return VK_UP;
	case GWindow::VK::RIGHTARROW:	       return VK_RIGHT;
	case GWindow::VK::DOWNARROW:	       return VK_DOWN;
	case GWindow::VK::SELECT:		       return VK_SELECT;
	case GWindow::VK::PRINT:	           return VK_PRINT;
	case GWindow::VK::EXECUTE:		       return VK_EXECUTE;
	case GWindow::VK::PRINT_SCREEN:	       return VK_SNAPSHOT;
	case GWindow::VK::INSERT:		       return VK_INSERT;
	case GWindow::VK::DEL:			       return VK_DELETE;
	case GWindow::VK::HELP:			       return VK_HELP;
	case GWindow::VK::KEY_0:			   return 0x30;
	case GWindow::VK::KEY_1:			   return 0x31;
	case GWindow::VK::KEY_2:			   return 0x32;
	case GWindow::VK::KEY_3:			   return 0x33;
	case GWindow::VK::KEY_4:			   return 0x34;
	case GWindow::VK::KEY_5:			   return 0x35;
	case GWindow::VK::KEY_6:			   return 0x36;
	case GWindow::VK::KEY_7:			   return 0x37;
	case GWindow::VK::KEY_8:			   return 0x38;
	case GWindow::VK::KEY_9:			   return 0x39;
	case GWindow::VK::A:				   return 0x41;
	case GWindow::VK::B:				   return 0x42;
	case GWindow::VK::C:				   return 0x43;
	case GWindow::VK::D:				   return 0x44;
	case GWindow::VK::E:				   return 0x45;
	case GWindow::VK::F:				   return 0x46;
	case GWindow::VK::G:				   return 0x47;
	case GWindow::VK::H:				   return 0x48;
	case GWindow::VK::I:				   return 0x49;
	case GWindow::VK::J:				   return 0x4a;
	case GWindow::VK::K:				   return 0x4b;
	case GWindow::VK::L:				   return 0x4c;
	case GWindow::VK::M:				   return 0x4d;
	case GWindow::VK::N:				   return 0x4e;
	case GWindow::VK::O:				   return 0x4f;
	case GWindow::VK::P:				   return 0x50;
	case GWindow::VK::Q:				   return 0x51;
	case GWindow::VK::R:				   return 0x52;
	case GWindow::VK::S:				   return 0x53;
	case GWindow::VK::T:				   return 0x54;
	case GWindow::VK::U:				   return 0x55;
	case GWindow::VK::V:				   return 0x56;
	case GWindow::VK::W:				   return 0x57;
	case GWindow::VK::X:				   return 0x58;
	case GWindow::VK::Y:				   return 0x59;
	case GWindow::VK::Z:				   return 0x5a;
	case GWindow::VK::LEFT_WINDOWS:	       return VK_LWIN;
	case GWindow::VK::RIGHT_WINDOWS:	   return VK_RWIN;
	case GWindow::VK::APPLICATION:	       return VK_APPS;
	case GWindow::VK::SLEEP:			   return VK_SLEEP;
	case GWindow::VK::SCROLL_LOCK:	       return VK_SCROLL;
	case GWindow::VK::LEFT_MENU:		   return VK_LMENU;
	case GWindow::VK::RIGHT_MENU:	       return VK_RMENU;
	case GWindow::VK::VOLUME_MUTE:	       return VK_VOLUME_MUTE;
	case GWindow::VK::VOLUME_DOWN:	       return VK_VOLUME_DOWN;
	case GWindow::VK::VOLUME_UP:		   return VK_VOLUME_UP;
	case GWindow::VK::MEDIA_NEXT:	       return VK_MEDIA_NEXT_TRACK;
	case GWindow::VK::MEDIA_LAST:	       return VK_MEDIA_PREV_TRACK;
	case GWindow::VK::MEDIA_STOP:	       return VK_MEDIA_STOP;
	case GWindow::VK::MEDIA_PLAY_PAUSE:    return VK_MEDIA_PLAY_PAUSE;
	case GWindow::VK::OEM_1:			   return VK_OEM_1;
	case GWindow::VK::OEM_2:			   return VK_OEM_2;
	case GWindow::VK::OEM_3:			   return VK_OEM_3;
	case GWindow::VK::OEM_4:			   return VK_OEM_4;
	case GWindow::VK::OEM_5:			   return VK_OEM_5;
	case GWindow::VK::OEM_6:			   return VK_OEM_6;
	case GWindow::VK::OEM_7:			   return VK_OEM_7;
	case GWindow::VK::OEM_8:			   return VK_OEM_8;
	case GWindow::VK::OEM_102:             return VK_OEM_102;
	case GWindow::VK::OEM_CLEAR:		   return VK_OEM_CLEAR;
	case GWindow::VK::OEM_PLUS:		       return VK_OEM_PLUS;
	case GWindow::VK::OEM_COMMA:		   return VK_OEM_COMMA;
	case GWindow::VK::OEM_MINUS:		   return VK_OEM_MINUS;
	case GWindow::VK::OEM_PERIOD:	       return VK_OEM_PERIOD;
	case GWindow::VK::NUMPAD_0:		       return VK_NUMPAD0;
	case GWindow::VK::NUMPAD_1:		       return VK_NUMPAD1;
	case GWindow::VK::NUMPAD_2:		       return VK_NUMPAD2;
	case GWindow::VK::NUMPAD_3:		       return VK_NUMPAD3;
	case GWindow::VK::NUMPAD_4:		       return VK_NUMPAD4;
	case GWindow::VK::NUMPAD_5:		       return VK_NUMPAD5;
	case GWindow::VK::NUMPAD_6:		       return VK_NUMPAD6;
	case GWindow::VK::NUMPAD_7:		       return VK_NUMPAD7;
	case GWindow::VK::NUMPAD_8:		       return VK_NUMPAD8;
	case GWindow::VK::NUMPAD_9:		       return VK_NUMPAD9;
	case GWindow::VK::NUMPAD_MULTIPLY:     return VK_MULTIPLY;
	case GWindow::VK::NUMPAD_ADD:	       return VK_ADD;
	case GWindow::VK::NUMPAD_SEPERATOR:    return VK_SEPARATOR;
	case GWindow::VK::NUMPAD_SUBTRACT:     return VK_SUBTRACT;
	case GWindow::VK::NUMPAD_COMMA:	       return VK_DECIMAL;
	case GWindow::VK::NUMPAD_DIVIDE:	   return VK_DIVIDE;
	case GWindow::VK::NUMPAD_LOCK:	       return VK_NUMLOCK;
	case GWindow::VK::F1:			       return VK_F1;
	case GWindow::VK::F2:			       return VK_F2;
	case GWindow::VK::F3:			       return VK_F3;
	case GWindow::VK::F4:			       return VK_F4;
	case GWindow::VK::F5:			       return VK_F5;
	case GWindow::VK::F6:			       return VK_F6;
	case GWindow::VK::F7:			       return VK_F7;
	case GWindow::VK::F8:			       return VK_F8;
	case GWindow::VK::F9:			       return VK_F9;
	case GWindow::VK::F10:			       return VK_F10;
	case GWindow::VK::F11:			       return VK_F11;
	case GWindow::VK::F12:			       return VK_F12;
	case GWindow::VK::F13:			       return VK_F13;
	case GWindow::VK::F14:			       return VK_F14;
	case GWindow::VK::F15:			       return VK_F15;
	case GWindow::VK::F16:			       return VK_F16;
	case GWindow::VK::F17:			       return VK_F17;
	case GWindow::VK::F18:			       return VK_F18;
	case GWindow::VK::F19:			       return VK_F19;
	case GWindow::VK::F20:			       return VK_F20;
	case GWindow::VK::F21:			       return VK_F21;
	case GWindow::VK::F22:			       return VK_F22;
	case GWindow::VK::F23:			       return VK_F23;
	case GWindow::VK::F24:			       return VK_F24;
	case GWindow::VK::PLAY:			       return VK_PLAY;
	case GWindow::VK::ZOOM:			       return VK_ZOOM;
	case GWindow::VK::UNKWON:              return -1;
	}
}

struct WrapperClass {
	GWindow::Window* window = nullptr;
	uint32_t thisID = 0;
	std::vector<GEventWrapper::GEventWindowState> windowStateFun;
	std::vector<GEventWrapper::GEventWindowResize> windowResizeFun;
	std::vector<GEventWrapper::GEventWindowFocus> windowFocusFun;
	std::vector<GEventWrapper::GEventWindowMove> windowMoveFun;
	std::vector<GEventWrapper::GEventKeyboard> keyboardFun;
	std::vector<GEventWrapper::GEventMouseButton> mouseButtonFun;
	std::vector<GEventWrapper::GEventMouseMove> mouseMoveFun;
	std::vector<GEventWrapper::GEventWindowClose> windowCloseFun;

	bool* keyPressed = nullptr;
	GGeneral::Point<int> mousePos;

	~WrapperClass() { delete[] keyPressed; }
};

std::vector<WrapperClass> allWrapper;

WrapperClass* getWrapperfromWindowID(int ID) {
	for (size_t i = 0; i < allWrapper.size(); i++) {
		if ((int)allWrapper[i].window->getID() == ID)
			return &allWrapper[i];
	}
	return nullptr;
}

void globalCallback(int id, GWindow::WindowEvent event, void* data) {
	switch (event) {
	case GWindow::WindowEvent::WINDOW_STATE:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->windowStateFun.size(); i++) {
			wrapper->windowStateFun[i](wrapper->window, (GWindow::WindowState)(int)data);
		}
		break;
	}
	case GWindow::WindowEvent::WINDOW_RESIZE:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->windowResizeFun.size(); i++) {
			wrapper->windowResizeFun[i](wrapper->window, *(GGeneral::Rectangle<long>*)data);
		}
		break;
	}
	case GWindow::WindowEvent::WINDOW_FOCUS:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->windowFocusFun.size(); i++) {
			wrapper->windowFocusFun[i](wrapper->window, (bool)data);
		}
		break;
	}
	case GWindow::WindowEvent::WINDOW_MOVE:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->windowMoveFun.size(); i++) {
			wrapper->windowMoveFun[i](wrapper->window, *(GGeneral::Point<long>*)data);
		}
		break;
	}
	case GWindow::WindowEvent::KEY_PRESS:
	{
		GWindow::VK key = (GWindow::VK)(int)data;
		//get window
		auto wrapper = getWrapperfromWindowID(id);
		wrapper->keyPressed[(int)key] = true;
		switch (key) {
		case GWindow::VK::LEFT_MB:
		case GWindow::VK::RIGHT_MB:
		case GWindow::VK::MIDDLE_MB:
		case GWindow::VK::X1_MB:
		case GWindow::VK::X2_MB:
			for (size_t i = 0; i < wrapper->mouseButtonFun.size(); i++)
				wrapper->mouseButtonFun[i](wrapper->window, true, (GEventWrapper::MouseButtons)(int)key);
			break;
		default:
			for (size_t i = 0; i < wrapper->keyboardFun.size(); i++)
				wrapper->keyboardFun[i](wrapper->window, true, key);
		}
		break;
	}
	case GWindow::WindowEvent::KEY_RELEASE:
	{
		//get window
		auto wrapper = getWrapperfromWindowID(id);
		GWindow::VK key = (GWindow::VK)(int)data;
		wrapper->keyPressed[(int)key] = false;
		switch (key) {
		case GWindow::VK::LEFT_MB:
		case GWindow::VK::RIGHT_MB:
		case GWindow::VK::MIDDLE_MB:
		case GWindow::VK::X1_MB:
		case GWindow::VK::X2_MB:
			for (size_t i = 0; i < wrapper->mouseButtonFun.size(); i++)
				wrapper->mouseButtonFun[i](wrapper->window, false, (GEventWrapper::MouseButtons)(int)key);
			break;
		default:
			for (size_t i = 0; i < wrapper->keyboardFun.size(); i++)
				wrapper->keyboardFun[i](wrapper->window, false, key);
		}
		break;
	}
	case GWindow::WindowEvent::MOUSE_MOVE:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->mouseMoveFun.size(); i++) {
			wrapper->mouseMoveFun[i](wrapper->window, *(GGeneral::Point<int>*)data);
		}
		wrapper->mousePos = *(GGeneral::Point<int>*)data;
		break;
	}
	case GWindow::WindowEvent::WINDOW_CLOSE:
	{
		auto wrapper = getWrapperfromWindowID(id);
		for (size_t i = 0; i < wrapper->windowCloseFun.size(); i++) {
			wrapper->windowCloseFun[i](wrapper->window);
		}
		break;
	}
	}
}

GEventWrapper::Windowhandler::Windowhandler() {
	this->ID = allWrapper.size() + 1;
	allWrapper.push_back(WrapperClass());
	THIS_INSTANCE.keyPressed = new bool[140];
	memset(THIS_INSTANCE.keyPressed, 0, sizeof(bool) * 140);
}
GEventWrapper::Windowhandler::Windowhandler(GWindow::Window* window) {
	this->ID = allWrapper.size() + 1;
	allWrapper.push_back(WrapperClass());
	THIS_INSTANCE.keyPressed = new bool[140];
	memset(THIS_INSTANCE.keyPressed, 0, sizeof(bool) * 140);
	registerWindow(window);
}

GEventWrapper::Windowhandler::~Windowhandler() {
	THIS_INSTANCE.window->setCallbackFunction(nullptr);
}

void GEventWrapper::Windowhandler::registerWindow(GWindow::Window* window) {
	if (THIS_INSTANCE.window != nullptr)
		THIS_INSTANCE.window->setCallbackFunction(nullptr);
	window->setCallbackFunction(globalCallback);
	THIS_INSTANCE.thisID = this->ID;
	THIS_INSTANCE.window = window;
}

void GEventWrapper::Windowhandler::addCallback(GEventWindowState callback) {
	THIS_INSTANCE.windowStateFun.push_back(callback);
}

void GEventWrapper::Windowhandler::addCallback(GEventWindowResize callback) {
	THIS_INSTANCE.windowResizeFun.push_back(callback);
}

void GEventWrapper::Windowhandler::addCallback(GEventWindowFocus callback) {
	THIS_INSTANCE.windowFocusFun.push_back(callback);
}

void GEventWrapper::Windowhandler::addCallback(GEventWindowMove callback) {
	THIS_INSTANCE.windowMoveFun.push_back(callback);
}

void GEventWrapper::Windowhandler::addCallback(GEventMouseButton f) {
	THIS_INSTANCE.mouseButtonFun.push_back(f);
}

void GEventWrapper::Windowhandler::addCallback(GEventMouseMove f) {
	THIS_INSTANCE.mouseMoveFun.push_back(f);
}

void GEventWrapper::Windowhandler::addCallback(GEventWindowClose callback) {
	THIS_INSTANCE.windowCloseFun.push_back(callback);
}

void GEventWrapper::Windowhandler::addCallback(GEventKeyboard f) {
	THIS_INSTANCE.keyboardFun.push_back(f);
}

bool GEventWrapper::Windowhandler::isKeyPressed(GWindow::VK key) {
	if (key == GWindow::VK::UNKWON)
		return false;
	return THIS_INSTANCE.keyPressed[(int)key];
}

GGeneral::Point<int> GEventWrapper::Windowhandler::getMousePosition() {
	return THIS_INSTANCE.mousePos;
}