#pragma once

#include "../GameManager.h"
#include "../../CLGEngine/TileMap.h"
#include "../../CLGEngine/CORE/Vector2.h"
#include "../../CLGEngine/Component/Collider.h"
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Component/Render.h"


class Character : public CLGEngine::Entity {
private:
	int _speed;
	bool _grounded;
	float _groundLevel;
	TileMap* _tileMap;
	CLGEngine::CORE::Vector2<float> _position;
	CLGEngine::Collider* _col;
	CLGEngine::Renderer* _rend;
	void AdjustRectAsNeeded();
public:
	GameManager* gm;
	Character(CLGEngine::CORE::Vector2<float> startPosition);
	~Character();
	void Update();

	void Move(float direction);
	void Jump();

	// TileMap
	void AddTileMap(TileMap* map);
};
