#pragma once

#include "../../CLGEngine/CORE/Vector2.h"
#include "../../CLGEngine/Entity.h"
#include "../../CLGEngine/Components/Renderers/TextRenderer.h"
#include <string>

class ScreenText 
    : public CLGEngine::Entity {
private:
public:
    CLGEngine::TextRenderer* _text;
    ScreenText(CLGEngine::Vector2<int> position);
    ~ScreenText();
    void Update() {};
    void SetText(std::string text);
};