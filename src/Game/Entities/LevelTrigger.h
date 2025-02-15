#pragma once

#include <string>
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/CORE/Vector2.h"
#include "../../CLGEngine/Components/Collider.h"
#include "../../CLGEngine/Components/Renderers/BlockRenderer.h"
#include "../GameManager.h"

class LevelTrigger
: public CLGEngine::Entity {
private:
    CLGEngine::Collider* _col;
    CLGEngine::BlockRenderer* _rend;
public:
    GameManager* gm;
    LevelTrigger(CLGEngine::Vector2<int> position, std::string levelName);
    ~LevelTrigger();
    void Update();
    void OnCollision(CLGEngine::Entity* hit);
};