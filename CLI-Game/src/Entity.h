 #pragma once

enum Cardinal {
	North,
	East,
	South,
	West
};

/// <summary>
/// Any "physical" thing that can be represented in "world-space"
/// </summary>
class Entity {
	private:
		int posX, posY;
	public:
		void Move(Cardinal direction);
};
