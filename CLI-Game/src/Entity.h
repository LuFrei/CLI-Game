 #pragma once

/// <summary>
/// Any "physical" thing that can be represented in "world-space". 
/// Such as a playable or non-playable character, floors, walls, props
/// </summary>
class Entity {
	private:
		int posX, posY;
	public:
		void Move(int x, int y);
};
