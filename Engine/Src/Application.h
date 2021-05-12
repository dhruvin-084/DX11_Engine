#pragma once

#include"Window.h"
#include"Keyboard.h"
#include"Timer.h"

class Application {
public:
	Application();
	int Start();
	void Update();
private:
	Window wnd;
	Keyboard keyboard;
	Timer timer;
};
