#include<Windows.h>
#include<functional>
#include<iostream>

#include"Window.h"
#include"Execption.h"

#include"Events/Event.h"
#include"Events/KeyboardEvents.h"

void HandleKeyBoardEvents(Event& e) {
	EventDispatcher dispatcher(e);

	dispatcher.Dispatch<KeyPressedEvent>([](KeyPressedEvent& e) {
		std::cout << e.ToString() << std::endl;
		return true;
	});
}

int main() {
	try {
		Window wnd(640, 480, "DX11 Engine");
		wnd.SetEventCallback(HandleKeyBoardEvents);

		// message pump
		MSG msg;
		while (GetMessage(&msg, nullptr, 0, 0) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
	}
	catch(Exception& e) {
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch(std::exception& e) {
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...) {
		MessageBox(nullptr, "No information available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}



	return 0;
}

