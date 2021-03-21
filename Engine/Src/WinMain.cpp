#include<Windows.h>

#include"Window.h"

int main() {
	Window wnd(640, 480, "DX11 Engine");

	// message pump
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return 0;
}