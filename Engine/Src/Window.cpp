#include"Window.h"


Window::Window(int _width, int _height, const char* name) :
	width(_width), height(_height) {

	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd = CreateWindowEx(
		0, WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT,
		wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);


	// show window
	ShowWindow(hWnd, SW_SHOW);
}

Window::~Window() {
	DestroyWindow(hWnd);
}

LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() :
	hInst(GetModuleHandle(nullptr)) {
	// register window class 
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsg;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszClassName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = nullptr;

	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass() {
	UnregisterClass(GetName(), GetInstance());
}

HINSTANCE Window::WindowClass::GetInstance() {
	return wndClass.hInst;
}

const char* Window::WindowClass::GetName() {
	return wndClassName;
}



