#pragma once
namespace CLGEngine {
	class Time {
		// Get time since last tick
	public:
		static float deltaTime;
		static void CalculateDeltaTime();
	};
}