#include"Window.h"

#include<sstream>

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

	// Event handaling
	SetEventCallback([this](Event& e) {
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& e) {
			this->keyboard.OnKeyPressed(e);
			return true;
		});
		dispatcher.Dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& e) {
			this->keyboard.OnKeyRelesed(e);
			return true;
		});
		dispatcher.Dispatch<KeyCharEvent>([this](KeyCharEvent& e) {
			this->keyboard.OnChar(e.GetKeyCode());
			return true;
		});
	});
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

Window::WindowExcetion::WindowExcetion(int line, const char* file, HRESULT hr) noexcept
	: Exception(line, file), hr(hr)
{}

const char* Window::WindowExcetion::what() const noexcept
{
	std::ostringstream oss;
	oss << "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::WindowExcetion::GetType() const noexcept
{
	return "Window Excetion";
}

std::string Window::WindowExcetion::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	if (nMsgLen == 0) {
		return "Unidentified error code";
	}
	std::string errorString = pMsgBuf;
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::WindowExcetion::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::WindowExcetion::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
