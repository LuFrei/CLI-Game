#pragma once
namespace CLGEngine {
	class Time {
		// Get time since last tick
	public:
		static float deltaTime;
		// TODO: We probably dont want this exposed.
		static void CalculateDeltaTime();
	};
}