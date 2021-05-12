#include"Timer.h"

Timer::Timer() {
	start = std::chrono::steady_clock::now();
	last = start;
}

float Timer::Time() {
	auto currentTime = std::chrono::steady_clock::now();
	auto time = currentTime - start;
	return time.count();
}

float Timer::Mark() {
	auto oldTime = last;
	last = std::chrono::steady_clock::now();
	auto markTime = last - oldTime;
	return markTime.count();
}