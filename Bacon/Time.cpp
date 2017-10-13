#include "stdafx.h"
#include "Time.h"

unsigned long Time::_frameCount;
double Time::_deltaTime;
std::chrono::high_resolution_clock::time_point Time::_oldClockTime;
std::chrono::high_resolution_clock::time_point Time::_clockTime;

void Time::Tick () {
	_frameCount++;
	_oldClockTime = (_oldClockTime != _clockTime ? _clockTime : std::chrono::high_resolution_clock::now ());
	_clockTime = std::chrono::high_resolution_clock::now ();
	_deltaTime = std::chrono::duration_cast<std::chrono::microseconds> (_clockTime - _oldClockTime).count () / 1000000.0;
}

double Time::DeltaTime () {
	return _deltaTime;
}

std::chrono::high_resolution_clock::time_point Time::CurrentTime () {
	return std::chrono::high_resolution_clock::now ();
}

unsigned long Time::FrameCount () {
	return _frameCount;
}