#pragma once

#include "../CLGEngine/CORE/Utility.h"
#include "../CLGEngine/Entity.h"
#include "../CLGEngine/Graphics/TextRenderer.h"

class ScreenText 
    : public CLGEngine::Entity {
private:
    TextRenderer* _text;
public:
    ScreenText(CLGEngine::CORE::Vector2<float> position);
    ~ScreenText();
};