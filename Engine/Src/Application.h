#pragma once

#include"Window.h"
#include"Keyboard.h"

class Application {
public:
	Application();
	int Start();
	void Update();
private:
	Window wnd;
	Keyboard keyboard;
};
