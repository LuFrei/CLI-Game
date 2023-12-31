 #pragma once

/// <summary>
/// Any "physical" thing that can be represented in "world-space". 
/// Such as a playable or non-playable character, floors, walls, props
/// </summary>
class Entity {
public:
	int x, y;
	unsigned int width, height;
	Entity();
	Entity(int x, int y, unsigned int width, unsigned int height);
	virtual void Move(int x, int y);
};
