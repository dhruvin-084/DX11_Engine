#include<Windows.h>
#include<functional>
#include<iostream>

#include"Application.h"
#include"Execption.h"

#include"Events/Event.h"
#include"Events/KeyboardEvents.h"


int main() {
	try {
		return Application{}.Start();
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

	return -1;
}

