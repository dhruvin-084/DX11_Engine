#pragma once

#include<Windows.h>

class Window {
public:
	Window(int _width, int _height, const char* name);
	~Window();

private:
	int width;
	int height;
	HWND hWnd;


private:
	class WindowClass {
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();

		static WindowClass wndClass;
		static constexpr const char* wndClassName = "DX11_Engine_class";
		HINSTANCE hInst;
	};


};
