#pragma once
namespace CLGEngine {
	class Time {
		// Get time since last tick
	public:
		static float deltaTime;
		// TODO: We probably dont want this exposed. Before moving to dedicated Engine, fix this.
		static void CalculateDeltaTime();
	};
}