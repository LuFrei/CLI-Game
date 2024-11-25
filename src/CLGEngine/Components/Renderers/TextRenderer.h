#pragma once

#include <string>
#include <vector>
#include "Renderer.h"
#include "../../CORE/Vector2.h"

namespace CLGEngine {
class TextRenderer
: public Renderer{
private:
    std::string _text;
public:
    bool autoSize = false;

    TextRenderer(Entity* ent, std::string text);
    ~TextRenderer();

    void SetText(std::string text);
    std::string GetText() {return _text;}
};
};