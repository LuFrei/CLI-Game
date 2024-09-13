#pragma once

#include <string>
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/CORE/Vector2.h"
#include "../CLGEngine/Component/Collider.h"
#include "../CLGEngine/Component/Render.h"

class LevelTrigger
: public CLGEngine::Entity {
private:
    CLGEngine::Collider* _col;
    Graphics::Renderer* _rend;
public:
    std::string levelTo;
    LevelTrigger(CLGEngine::CORE::Vector2<int> position, std::string levelName);
    ~LevelTrigger();
    void Update();
};