#include"Window.h"
#include"Exceptions/WindowException.h"

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
	if (hWnd == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	// set winData as window's user data
	SetWindowLongPtrA(hWnd, GWLP_USERDATA, (LONG_PTR)&winData);

	// show window
	ShowWindow(hWnd, SW_SHOW);

	// initialize graphics
	pGfx = std::make_unique<Graphics>(hWnd);
}

Window::~Window() {
	DestroyWindow(hWnd);
}



// implemented in Src/MessasgeHndler.cpp
LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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



std::optional<int> Window::ProcessMessages()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			return (int)msg.wParam;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return {};
}

void Window::SetWindowTitle(const char* title)
{
	if(!SetWindowText(hWnd, title))
		throw WND_LAST_EXCEPT();
}

Graphics& Window::Gfx()
{
	return *pGfx;
}
