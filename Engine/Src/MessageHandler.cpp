#include<Windows.h>
#include<functional>

#include"Events/Event.h"
#include"Events/KeyboardEvents.h"

struct windowData {
	std::function<void(Event&)> EventCallback;
};


LRESULT CALLBACK HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	windowData* winData = (windowData*)GetWindowLongPtrA(hWnd, GWLP_USERDATA);

	switch (msg) {
	case WM_KEYDOWN: 
	{
		int repeatCount = lParam & 0xF0;
		KeyPressedEvent e(wParam, repeatCount);
		winData->EventCallback(e);
		break;
	}
	case WM_KEYUP:
	{
		KeyReleasedEvent e(wParam);
		winData->EventCallback(e);
		break;
	}

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}