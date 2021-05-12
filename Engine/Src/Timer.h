#pragma once
#include<chrono>

class Timer {
public:
	Timer();
	float Time();
	float Mark();
private:
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point start;
};
