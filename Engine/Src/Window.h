#pragma once

#include<Windows.h>
#include<functional>
#include<optional>
#include<memory>

#include"Events/Event.h"
#include"Keyboard.h"
#include"Graphics.h"

class Window {
public:
	Window(int _width, int _height, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window operator=(const Window&) = delete;

	inline void SetEventCallback(const std::function<void(Event&)>& callback) { winData.EventCallback = callback; };
	static std::optional<int> ProcessMessages();
	void SetWindowTitle(const char* title);
	Graphics& Gfx();

private:
	int width;
	int height;
	HWND hWnd;
	std::unique_ptr<Graphics> pGfx;

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

