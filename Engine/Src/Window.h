#pragma once

#include<Windows.h>
#include<functional>

#include"Events/Event.h"

class Window {
public:
	Window(int _width, int _height, const char* name);
	~Window();

	inline void SetEventCallback(const std::function<void(Event&)>& callback) { winData.EventCallback = callback; };

private:
	int width;
	int height;
	HWND hWnd;
	
	struct windowData {
		std::function<void(Event&)> EventCallback;
	};

	windowData winData;


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
