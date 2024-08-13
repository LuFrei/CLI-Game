#pragma once
#include "../CLGEngine/Entity.h"
#include "TileMap.h"
#include "../CLGEngine/CORE/Utility.h"

using namespace CLGEngine;

class Character : public Entity {
private:
	int _speed;
	bool _grounded;
	float _groundLevel;
	TileMap* _tileMap;
	CORE::Vector2<float> _position;

	bool CheckTileMapCollision();
public:
	Character(CORE::Vector2<float> startPosition);
	~Character();
	void Update();

	void Move(float direction);
	void Jump();

	// TileMap
	void AddTileMap(TileMap* map);
};