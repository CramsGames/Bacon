#pragma once
#include <chrono>

class Time {
public:
	static void Tick ();
	static unsigned long FrameCount ();
	static double DeltaTime ();
	static std::chrono::high_resolution_clock::time_point CurrentTime ();
private:
	static unsigned long _frameCount;
	static double _deltaTime;
	static std::chrono::high_resolution_clock::time_point _oldClockTime;
	static std::chrono::high_resolution_clock::time_point _clockTime;
};