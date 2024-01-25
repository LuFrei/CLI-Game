#include "Time.h"

#include <Windows.h>
#include <chrono>

namespace CLGEngine {
	float Time::deltaTime;
	std::chrono::steady_clock::time_point lastUpdate;

	void Time::CalculateDeltaTime() {
		auto now = std::chrono::steady_clock::now();
		Time::deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
		lastUpdate = now;
	}
}