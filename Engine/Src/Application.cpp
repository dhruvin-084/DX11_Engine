#include "Application.h"
#include<iostream>

Application::Application()
	: wnd(640, 480, "DX11 Engine")
{
	// Event handaling
	wnd.SetEventCallback([this](Event& e) {
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

int Application::Start()
{
	while (true) {
		if (const auto ecode = Window::ProcessMessages()) {
			return *ecode;
		}

		Update();
	}

	return -1;
}

void Application::Update()
{

	wnd.Gfx().ClearBuffer(0.5f, 0.5f, 1.0f);
	wnd.Gfx().DrawTestTriangle();
	wnd.Gfx().EndFrame();
}
