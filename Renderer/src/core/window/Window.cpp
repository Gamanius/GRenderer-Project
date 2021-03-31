#undef UNICODE
#include <Windows.h>
#include <Windowsx.h>
#include "GRenderer.h"
#include <map>
#include <gl/glew.h>


//https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_create_context.txt
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB               0x2093
#define WGL_CONTEXT_FLAGS_ARB                     0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB          0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

#define WGL_CONTEXT_DEBUG_BIT_ARB                 0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB    0x0002

//need to load this function in
typedef HGLRC WINAPI wglCreateContextAttribsARB_type(HDC hdc, HGLRC hShareContext, const int* attribList);
wglCreateContextAttribsARB_type* wglCreateContextAttribsARB;

//WinAPI specific variables
static MSG msg;
HINSTANCE hInstance = GetModuleHandle(0);
HGLRC hglrc = NULL;

//static vars needed to keep track of all instances
std::map<HWND, GWindow::Window*> allWindowInstances;

//OpenGL hints
byte CONTEXT_MAJOR = 3;
byte CONTEXT_MINOR = 3;
byte PROFILE_FLAG  = 1;
byte CONTEXT_FLAG  = 0;

//declare function that is at the end of this document
static int getWindowsVirtualKeyCode(GWindow::VK key);
static GWindow::VK getVirtualKeyCode(int windowsKey);

bool GWindow::init() {
	//Need to create a dummy window class
	WNDCLASSA dummyWindowClass = {};
	dummyWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	dummyWindowClass.lpfnWndProc = DefWindowProcA;
	dummyWindowClass.hInstance = GetModuleHandle(0);
	dummyWindowClass.lpszClassName = "Dummy_WGL_djuasiodwa";

	if (!RegisterClassA(&dummyWindowClass)) {
		THROW("Couldn't register window");
		return false;
	}

	HWND dummyWindow = CreateWindowExA(
		0,
		dummyWindowClass.lpszClassName,
		"Dummy OpenGL Window",
		0,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		0,
		0,
		dummyWindowClass.hInstance,
		0);

	if (!dummyWindow) {
		THROW("Couldn't create window");
		return false;
	}

	HDC dummy_dc = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.cColorBits = 32;
	pfd.cAlphaBits = 8;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 8;

	int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
	if (!pixel_format) {
		THROW("Couldn't choose pixel format");
		return false;
	}
	if (!SetPixelFormat(dummy_dc, pixel_format, &pfd)) {
		THROW("Couldn't set pixel format");
		return false;
	}

	HGLRC dummy_context = wglCreateContext(dummy_dc);
	if (!dummy_context) {
		THROW("Couldn't create context");
		return false;
	}

	if (!wglMakeCurrent(dummy_dc, dummy_context)) {
		THROW("Couldn't set context active");
		return false;
	}

	wglCreateContextAttribsARB = (wglCreateContextAttribsARB_type*) wglGetProcAddress("wglCreateContextAttribsARB");
	if (glewInit() != GLEW_OK) {
		THROWF("Couldn't load OpenGL functions");
		return false;
	}

	wglMakeCurrent(dummy_dc, 0);
	wglDeleteContext(dummy_context);
	ReleaseDC(dummyWindow, dummy_dc);
	DestroyWindow(dummyWindow);
	return true;
}

GGeneral::Rectangle<long> rectToGRectangle(const RECT& a) {
	GGeneral::Rectangle<long> rec;
	rec.dimension.width = a.right - a.left;
	rec.dimension.height = a.bottom - a.top;
	rec.position.x = a.left;
	rec.position.y = a.top;

	return rec;
}

//Will only check for CTRL, ALT and SHIFT. It is rather ugly but it gets the job done
std::vector<GWindow::VK> processUnknownKeys(bool pressed) {
	std::vector<GWindow::VK> returnValue;
	static int keyToCheck[6] = {
		//Shift               //Control                 //Alt
		VK_LSHIFT, VK_RSHIFT, VK_LCONTROL, VK_RCONTROL, VK_LMENU, VK_RMENU
	};

	static bool wasPressed[] = {
		0, 0, 0, 0, 0, 0
	};

	for (byte i = 0; i < 6; i++) {
		auto key = GetKeyState(keyToCheck[i]);
		char isPressed = (key & -128) + 129;
		if (isPressed == 1 && pressed) {
			wasPressed[i] = true;
			returnValue.push_back(getVirtualKeyCode(keyToCheck[i]));
		}
		else if (isPressed != 1 && !pressed && wasPressed[i]) {
			wasPressed[i] = false;
			returnValue.push_back(getVirtualKeyCode(keyToCheck[i]));
		}
	}

	return returnValue;
}

//window call back
LRESULT Callback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if(allWindowInstances[hWnd] == nullptr) {
		return  DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	switch (uMsg) {
	//Send close message
	case WM_CLOSE:
	{
		allWindowInstances[hWnd]->sendCloseRequest();
		return 0;
	}
	//do this to stop the flashin while resizing a window
	case WM_ERASEBKGND: return 0;
	//This will be called if the actual size has been changed by the user
	case WM_SIZING:
	{
		auto area = (RECT*)lParam;

		GGeneral::Rectangle<long> rec = rectToGRectangle(*area);

		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_RESIZE, (void*)&rec);
		return MAKELRESULT(1, 1);
	}
	//Will be sent if the size has been changed...or rather the state?
	case WM_SIZE:
	{
		if (wParam == 0 || wParam == 2) {
			if (!wParam)
				allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_STATE, (void*)GWindow::WindowState::NORMAL);
			else
				allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_STATE, (void*)GWindow::WindowState::MAXIMIZED);
			RECT area = {};
			GetWindowRect(hWnd, &area);
			GGeneral::Rectangle<long> rec = rectToGRectangle(area);

			allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_RESIZE, (void*)&rec);
		}
		else if (wParam) {
			allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_STATE, (void*)GWindow::WindowState::MINIMIZED);
		}
		
		return 0;
	}
	//Will be sent if the user is changing the postion of the window
	case WM_MOVING:
	{
		auto pos = (RECT*)lParam;
		auto p = GGeneral::Point<long>(pos->left, pos->top);
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_MOVE, (void*)&p);
		return 0;
	}
	//focus things
	case WM_SETFOCUS:
	{
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_FOCUS, (void*)true);
		return 0;
	}
	case WM_KILLFOCUS:
	{
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::WINDOW_FOCUS, (void*)false);
		return 0;
	}
	//key up and down events
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		//Window press event
		auto key = getVirtualKeyCode(wParam);
		if (key == GWindow::VK::UNKWON) {
			auto moreKeys = processUnknownKeys(true);
			for (size_t i = 0; i < moreKeys.size(); i++) {
				allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)moreKeys[i]);
			}
		}
		else
			allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)key);
		return MAKELRESULT(1, 1);
	}
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		auto key = getVirtualKeyCode(wParam);
		if (key == GWindow::VK::UNKWON) {
			auto moreKeys = processUnknownKeys(false);
			for (size_t i = 0; i < moreKeys.size(); i++) {
				allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)moreKeys[i]);
			}
		}
		else
			allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_RELEASE, (void*)key);
		return MAKELRESULT(1, 1);
	}
	//mouse move event
	case WM_MOUSEMOVE:
	{
		auto p = GGeneral::Point<int>(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::MOUSE_MOVE, (void*)&p);
		return 0;
	}
	//even more mouse stuff
	case WM_LBUTTONDOWN:
	{
		SetCapture(hWnd);
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)GWindow::VK::LEFT_MB);
		return MAKELRESULT(1, 1);
	}
	case WM_RBUTTONDOWN:
	{
		SetCapture(hWnd);
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)GWindow::VK::RIGHT_MB);
		return MAKELRESULT(1, 1);
	}
	case WM_XBUTTONDOWN:
	{
		SetCapture(hWnd);

		GWindow::VK key;
		if (GET_XBUTTON_WPARAM(wParam) == 1)
			 key = GWindow::VK::X1_MB;
		else
			key = GWindow::VK::X2_MB;

		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)key);
		return MAKELRESULT(1, 1);
	}
	case WM_MBUTTONDOWN:
	{
		SetCapture(hWnd);
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_PRESS, (void*)GWindow::VK::MIDDLE_MB);
		return MAKELRESULT(1, 1);
	}
	//mouse button release messages
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_RELEASE, (void*)GWindow::VK::LEFT_MB);
		return MAKELRESULT(1, 1);
	}
	case WM_RBUTTONUP:
	{
		ReleaseCapture();
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_RELEASE, (void*)GWindow::VK::RIGHT_MB);
		return MAKELRESULT(1, 1);
	}
	case WM_XBUTTONUP:
	{
		ReleaseCapture();
		GWindow::VK key;
		if (GET_XBUTTON_WPARAM(wParam) == 1)
			key = GWindow::VK::X1_MB;
		else
			key = GWindow::VK::X2_MB;

		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_RELEASE, (void*)key);
		return MAKELRESULT(1, 1);
	}
	case WM_MBUTTONUP:
	{
		ReleaseCapture();
		allWindowInstances[hWnd]->sendMessage(GWindow::WindowEvent::KEY_RELEASE, (void*)GWindow::VK::MIDDLE_MB);
		return MAKELRESULT(1, 1);
	}
	//Do this so the cursor looks good i guess???
	case WM_SETCURSOR:
	{
		if (LOWORD(lParam) == HTCLIENT) {
			SetCursor(LoadCursorA(NULL, IDC_ARROW));
			return true;
		}
		break;
	}
	//Do minimum and maximum window size
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = allWindowInstances[hWnd]->getMinimumWindowSize().width;
		lpMMI->ptMinTrackSize.y = allWindowInstances[hWnd]->getMinimumWindowSize().height;
		return 0;
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

GWindow::Window::Window(GGeneral::String name, GGeneral::Point<int> pos, GGeneral::Dimension<int> dim) {
	//Initialize the toilet
	WNDCLASS wc = {};
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)Callback;
	wc.hInstance = hInstance;
	wc.hbrBackground = CreateSolidBrush(3289650); //Some wonderfull gray shade!
	GGeneral::String s = "G-Renderer Instance " + name;
	wc.lpszClassName = s.cStr();

	if (!RegisterClassA(&wc)) THROW("An error occurred while registering the window");

	HWND hWnd = CreateWindowA(wc.lpszClassName, name.cStr(), WS_OVERLAPPEDWINDOW, pos.x, pos.y, dim.width, dim.height, 0, 0, hInstance, 0);
	if (!hWnd) {
		THROW("An error occurred while creating the window");
		return;
	}

	HDC hdc = GetDC(hWnd);

	this->WindowID = hWnd;
	this->deviceContext = hdc;
	EnableWindow(hWnd, true);

	//Pixel format
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	//Set pixel format
	auto iPixelFormat = ChoosePixelFormat((HDC)this->deviceContext, &pfd);
	if (!iPixelFormat) THROW("Couldn't choose pixel format");
	if (!SetPixelFormat((HDC)this->deviceContext, iPixelFormat, &pfd)) THROW("Couldn't set pixel format");

	allWindowInstances[hWnd] = this;
}

GWindow::Window::~Window() {
	allWindowInstances.erase((HWND)this->WindowID);
	this->setOpenGLContextActive(false);
	ReleaseDC((HWND)this->WindowID, (HDC)this->deviceContext);
	DeleteDC((HDC)this->deviceContext);
	DestroyWindow((HWND)this->WindowID);
}

void GWindow::Window::setWindowHints(ContextHints c, uint32_t value) {
	switch (c) {
	case GWindow::Window::ContextHints::MAJOR_VERSION:
		CONTEXT_MAJOR = value;
		break;
	case GWindow::Window::ContextHints::MINOR_VERSION:
		CONTEXT_MINOR = value;
		break;
	case GWindow::Window::ContextHints::PROFILE_MASK:
		if (value == 1)
			PROFILE_FLAG = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
		else if (value == 0)
			PROFILE_FLAG = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
		break;
	case GWindow::Window::ContextHints::CONTEXT_FLAGS:
		switch (value) {
		case 1:
			CONTEXT_FLAG = WGL_CONTEXT_DEBUG_BIT_ARB; break;
		case 2:
			CONTEXT_FLAG = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB; break;
		default:
			CONTEXT_FLAG = 0; 
		}
		break;
	}
}

bool GWindow::Window::createOpenGLcontext() {
	if (CONTEXT_FLAG != 0) {
		int gl33_attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, CONTEXT_MAJOR,
			WGL_CONTEXT_MINOR_VERSION_ARB, CONTEXT_MINOR,
			WGL_CONTEXT_PROFILE_MASK_ARB,  PROFILE_FLAG,
			WGL_CONTEXT_FLAGS_ARB,         CONTEXT_FLAG,
			0,
		};
		hglrc = wglCreateContextAttribsARB((HDC)this->deviceContext, 0, gl33_attribs);
	}

	if (hglrc == NULL) {
		if (CONTEXT_FLAG != 0) 
			THROWW("Couldn't create OpenGL context with given Context flags");
		int gl33_attribs[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, CONTEXT_MAJOR,
			WGL_CONTEXT_MINOR_VERSION_ARB, CONTEXT_MINOR,
			WGL_CONTEXT_PROFILE_MASK_ARB,  PROFILE_FLAG,
			0,                             0,
			0,
		};
		hglrc = wglCreateContextAttribsARB((HDC)this->deviceContext, 0, gl33_attribs);
	}


	if (hglrc == NULL) {
		THROW("Couldn't create OpenGL context");
		return false;
	}

	return true;
}

bool GWindow::Window::setOpenGLContextActive(bool b) {
	return wglMakeCurrent((HDC)this->deviceContext, b ? hglrc : NULL);
}

bool GWindow::Window::swapBuffers() {
	return SwapBuffers((HDC)this->deviceContext);
}

void GWindow::Window::setState(GWindow::WindowState state) {
	int nCmdShow = 0;
	switch (state) {
	case WindowState::HIDDEN:    nCmdShow = SW_HIDE;     break;
	case WindowState::MAXIMIZED: nCmdShow = SW_MAXIMIZE; break;
	case WindowState::NORMAL:    nCmdShow = SW_RESTORE;  break;
	case WindowState::MINIMIZED: nCmdShow = SW_MINIMIZE; break;
	}
	ShowWindow((HWND)this->WindowID, nCmdShow);
}

void GWindow::Window::fetchEvents(bool blocking) {
	BOOL result;

	//first block
	if (blocking)
		result = GetMessage(&msg, 0, 0, 0);
	else 
		result = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);

	while (result != 0) {
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		//now just peek messages
		result = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
	}
}

const bool GWindow::Window::getCloseRequest() const {
	return this->closeRequest;
}

void GWindow::Window::sendCloseRequest() {
	this->closeRequest = true;
}

GWindow::WindowState GWindow::Window::getCurrentWindowState() const {
	WINDOWPLACEMENT state;
	state.length = sizeof(state);
	GetWindowPlacement((HWND)this->WindowID, &state);
	switch (state.showCmd) {
	case SW_HIDE: return GWindow::WindowState::HIDDEN;
	case SW_MAXIMIZE: return GWindow::WindowState::MAXIMIZED;
	case SW_SHOWMINIMIZED:
	case SW_MINIMIZE: return GWindow::WindowState::MINIMIZED;
	default: return GWindow::WindowState::NORMAL;
	};
}

void GWindow::Window::setResizable(bool b) {
	if (!b)
		SetWindowLong((HWND)this->WindowID, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX);
	else
		SetWindowLong((HWND)this->WindowID, GWL_STYLE, WS_OVERLAPPEDWINDOW);
}

void GWindow::Window::setMinimumWindowSize(GGeneral::Dimension<int> size) {
	minimumWindowSize = size;
}

GGeneral::Dimension<int> GWindow::Window::getMinimumWindowSize() {
	return minimumWindowSize;
}


GGeneral::Dimension<int> GWindow::Window::getWindowSize() const {
	RECT rect = {};
	GetWindowRect((HWND)this->WindowID, &rect);
	return GGeneral::Dimension<int>(rect.right - rect.left, rect.bottom - rect.top);
}

GGeneral::Dimension<int> GWindow::Window::getWindowDrawSize() const {
	RECT rect = {};
	GetClientRect((HWND)this->WindowID, &rect);
	return GGeneral::Dimension<int>(rect.right - rect.left, rect.bottom - rect.top);
}

void GWindow::Window::setIcon(GGeneral::String filepath) const {
	auto handle = LoadImage(NULL, filepath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	if (handle == nullptr) {
		THROW("An Error occurred while loading image from filepath: '", filepath, "'. #", GetLastError());
	}
	SetClassLongPtr((HWND)this->WindowID, GCLP_HICON, (LONG)handle);
}

void GWindow::Window::setCallbackFunction(GWindowCallback fun) {
	this->callbackFunction = fun;
}

void GWindow::Window::sendMessage(WindowEvent event, void* data) {
	if(callbackFunction != nullptr)
		callbackFunction((int)this->WindowID, event, data);
}

static GWindow::VK getVirtualKeyCode(int windowsKey) {
	switch (windowsKey) {
	case VK_LBUTTON:                           return GWindow::VK::LEFT_MB;
	case VK_RBUTTON:		                   return GWindow::VK::RIGHT_MB;
	case VK_CANCEL:			                   return GWindow::VK::CANCEL;
	case VK_MBUTTON:		                   return GWindow::VK::MIDDLE_MB;
	case VK_XBUTTON1:		                   return GWindow::VK::X1_MB;
	case VK_XBUTTON2:		                   return GWindow::VK::X2_MB;
	case VK_LSHIFT:			                   return GWindow::VK::LEFT_SHIFT;
	case VK_RSHIFT:			                   return GWindow::VK::RIGHT_SHIFT;
	case VK_LCONTROL:		                   return GWindow::VK::LEFT_CONTROL;
	case VK_RCONTROL:		                   return GWindow::VK::RIGHT_CONTROL;
	case VK_BACK:			                   return GWindow::VK::BACKSPACE;
	case VK_TAB:			                   return GWindow::VK::TAB;
	case VK_RETURN:			                   return GWindow::VK::ENTER;
	case VK_MENU:			                   return GWindow::VK::ALT;
	case VK_PAUSE:			                   return GWindow::VK::PAUSE;
	case VK_CAPITAL:		                   return GWindow::VK::CAPSLOCK;
	case VK_ESCAPE:			                   return GWindow::VK::ESCAPE;
	case VK_SPACE:			                   return GWindow::VK::SPACE;
	case VK_PRIOR:			                   return GWindow::VK::PAGE_UP;
	case VK_NEXT:			                   return GWindow::VK::PAGE_DOWN;
	case VK_END:			                   return GWindow::VK::END;
	case VK_HOME:			                   return GWindow::VK::HOME;
	case VK_LEFT:			                   return GWindow::VK::LEFTARROW;
	case VK_UP:				                   return GWindow::VK::UPARROW;
	case VK_RIGHT:			                   return GWindow::VK::RIGHTARROW;
	case VK_DOWN:			                   return GWindow::VK::DOWNARROW;
	case VK_SELECT:			                   return GWindow::VK::SELECT;
	case VK_PRINT:			                   return GWindow::VK::PRINT;
	case VK_EXECUTE:		                   return GWindow::VK::EXECUTE;
	case VK_SNAPSHOT:		                   return GWindow::VK::PRINT_SCREEN;
	case VK_INSERT:			                   return GWindow::VK::INSERT;
	case VK_DELETE:			                   return GWindow::VK::DEL;
	case VK_HELP:			                   return GWindow::VK::HELP;
	case 0x30:				                   return GWindow::VK::KEY_0;
	case 0x31:				                   return GWindow::VK::KEY_1;
	case 0x32:				                   return GWindow::VK::KEY_2;
	case 0x33:				                   return GWindow::VK::KEY_3;
	case 0x34:				                   return GWindow::VK::KEY_4;
	case 0x35:				                   return GWindow::VK::KEY_5;
	case 0x36:				                   return GWindow::VK::KEY_6;
	case 0x37:				                   return GWindow::VK::KEY_7;
	case 0x38:				                   return GWindow::VK::KEY_8;
	case 0x39:				                   return GWindow::VK::KEY_9;
	case 0x41:				                   return GWindow::VK::A;
	case 0x42:				                   return GWindow::VK::B;
	case 0x43:				                   return GWindow::VK::C;
	case 0x44:				                   return GWindow::VK::D;
	case 0x45:				                   return GWindow::VK::E;
	case 0x46:				                   return GWindow::VK::F;
	case 0x47:				                   return GWindow::VK::G;
	case 0x48:				                   return GWindow::VK::H;
	case 0x49:				                   return GWindow::VK::I;
	case 0x4a:				                   return GWindow::VK::J;
	case 0x4b:				                   return GWindow::VK::K;
	case 0x4c:				                   return GWindow::VK::L;
	case 0x4d:				                   return GWindow::VK::M;
	case 0x4e:				                   return GWindow::VK::N;
	case 0x4f:				                   return GWindow::VK::O;
	case 0x50:				                   return GWindow::VK::P;
	case 0x51:				                   return GWindow::VK::Q;
	case 0x52:				                   return GWindow::VK::R;
	case 0x53:				                   return GWindow::VK::S;
	case 0x54:				                   return GWindow::VK::T;
	case 0x55:				                   return GWindow::VK::U;
	case 0x56:				                   return GWindow::VK::V;
	case 0x57:				                   return GWindow::VK::W;
	case 0x58:				                   return GWindow::VK::X;
	case 0x59:				                   return GWindow::VK::Y;
	case 0x5a:				                   return GWindow::VK::Z;
	case VK_LWIN:			                   return GWindow::VK::LEFT_WINDOWS;
	case VK_RWIN:			                   return GWindow::VK::RIGHT_WINDOWS;
	case VK_APPS:			                   return GWindow::VK::APPLICATION;
	case VK_SLEEP:			                   return GWindow::VK::SLEEP;
	case VK_SCROLL:			                   return GWindow::VK::SCROLL_LOCK;
	case VK_LMENU:			                   return GWindow::VK::LEFT_MENU;
	case VK_RMENU:			                   return GWindow::VK::RIGHT_MENU;
	case VK_VOLUME_MUTE:	                   return GWindow::VK::VOLUME_MUTE;
	case VK_VOLUME_DOWN:	                   return GWindow::VK::VOLUME_DOWN;
	case VK_VOLUME_UP:		                   return GWindow::VK::VOLUME_UP;
	case VK_MEDIA_NEXT_TRACK:                  return GWindow::VK::MEDIA_NEXT;
	case VK_MEDIA_PREV_TRACK:                  return GWindow::VK::MEDIA_LAST;
	case VK_MEDIA_STOP:		                   return GWindow::VK::MEDIA_STOP;
	case VK_MEDIA_PLAY_PAUSE:                  return GWindow::VK::MEDIA_PLAY_PAUSE;
	case VK_OEM_1:			                   return GWindow::VK::OEM_1;
	case VK_OEM_2:			                   return GWindow::VK::OEM_2;
	case VK_OEM_3:			                   return GWindow::VK::OEM_3;
	case VK_OEM_4:			                   return GWindow::VK::OEM_4;
	case VK_OEM_5:			                   return GWindow::VK::OEM_5;
	case VK_OEM_6:			                   return GWindow::VK::OEM_6;
	case VK_OEM_7:			                   return GWindow::VK::OEM_7;
	case VK_OEM_8:			                   return GWindow::VK::OEM_8;
	case VK_OEM_102:                           return GWindow::VK::OEM_102;
	case VK_OEM_CLEAR:		                   return GWindow::VK::OEM_CLEAR;
	case VK_OEM_PLUS:		                   return GWindow::VK::OEM_PLUS;
	case VK_OEM_COMMA:		                   return GWindow::VK::OEM_COMMA;
	case VK_OEM_MINUS:		                   return GWindow::VK::OEM_MINUS;
	case VK_OEM_PERIOD:		                   return GWindow::VK::OEM_PERIOD;
	case VK_NUMPAD0:		                   return GWindow::VK::NUMPAD_0;
	case VK_NUMPAD1:		                   return GWindow::VK::NUMPAD_1;
	case VK_NUMPAD2:		                   return GWindow::VK::NUMPAD_2;
	case VK_NUMPAD3:		                   return GWindow::VK::NUMPAD_3;
	case VK_NUMPAD4:		                   return GWindow::VK::NUMPAD_4;
	case VK_NUMPAD5:		                   return GWindow::VK::NUMPAD_5;
	case VK_NUMPAD6:		                   return GWindow::VK::NUMPAD_6;
	case VK_NUMPAD7:		                   return GWindow::VK::NUMPAD_7;
	case VK_NUMPAD8:		                   return GWindow::VK::NUMPAD_8;
	case VK_NUMPAD9:		                   return GWindow::VK::NUMPAD_9;
	case VK_MULTIPLY:		                   return GWindow::VK::NUMPAD_MULTIPLY;
	case VK_ADD:			                   return GWindow::VK::NUMPAD_ADD;
	case VK_SEPARATOR:		                   return GWindow::VK::NUMPAD_SEPERATOR;
	case VK_SUBTRACT:		                   return GWindow::VK::NUMPAD_SUBTRACT;
	case VK_DECIMAL:		                   return GWindow::VK::NUMPAD_COMMA;
	case VK_DIVIDE:			                   return GWindow::VK::NUMPAD_DIVIDE;
	case VK_NUMLOCK:		                   return GWindow::VK::NUMPAD_LOCK;
	case VK_F1:				                   return GWindow::VK::F1;
	case VK_F2:				                   return GWindow::VK::F2;
	case VK_F3:				                   return GWindow::VK::F3;
	case VK_F4:				                   return GWindow::VK::F4;
	case VK_F5:				                   return GWindow::VK::F5;
	case VK_F6:				                   return GWindow::VK::F6;
	case VK_F7:				                   return GWindow::VK::F7;
	case VK_F8:				                   return GWindow::VK::F8;
	case VK_F9:				                   return GWindow::VK::F9;
	case VK_F10:			                   return GWindow::VK::F10;
	case VK_F11:			                   return GWindow::VK::F11;
	case VK_F12:			                   return GWindow::VK::F12;
	case VK_F13:			                   return GWindow::VK::F13;
	case VK_F14:			                   return GWindow::VK::F14;
	case VK_F15:			                   return GWindow::VK::F15;
	case VK_F16:			                   return GWindow::VK::F16;
	case VK_F17:			                   return GWindow::VK::F17;
	case VK_F18:			                   return GWindow::VK::F18;
	case VK_F19:			                   return GWindow::VK::F19;
	case VK_F20:			                   return GWindow::VK::F20;
	case VK_F21:			                   return GWindow::VK::F21;
	case VK_F22:			                   return GWindow::VK::F22;
	case VK_F23:			                   return GWindow::VK::F23;
	case VK_F24:			                   return GWindow::VK::F24;
	case VK_PLAY:			                   return GWindow::VK::PLAY;
	case VK_ZOOM: 			                   return GWindow::VK::ZOOM;
	default:				                   return GWindow::VK::UNKWON;
	}
}

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
