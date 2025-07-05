#pragma once

#include <string>
#include <vector>
#include "libclr.h" // Imports Color
#include "Renderer.h"
#include "../../CORE/Vector2.h"

namespace CLGEngine {
class TextRenderer
: public Renderer{
private:
    std::string _text;
public:
    bool autoSize = false;

    unsigned short textColor = WHITE;       // May need clr:: prefix
    unsigned short backgroundColor = BLACK; // May need clr:: prefix

    TextRenderer(Entity* ent, std::string text);
    ~TextRenderer();

    void SetText(std::string text);
    std::string GetText() {return _text;}
};
};