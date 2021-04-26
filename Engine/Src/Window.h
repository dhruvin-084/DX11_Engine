#pragma once

#include<Windows.h>
#include<functional>
#include<optional>
#include<memory>

#include"Events/Event.h"
#include"Execption.h"
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
	Graphics& Gfx();

	class WindowExcetion : public Exception {
	public:
		WindowExcetion(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept override;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;


	private:
		HRESULT hr;
	};

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

// excetption helper macro;
#define WND_EXCEPT(hr) Window::WindowExcetion(__LINE__, __FILE__, hr)
#define WND_LAST_EXCEPT() Window::WindowExcetion(__LINE__, __FILE__, GetLastError())
