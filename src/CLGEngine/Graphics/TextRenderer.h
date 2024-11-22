#pragma once

#include <string>
#include <vector>
#include "../CORE/Vector2.h"

namespace CLGEngine {
class TextRenderer{
private:
    static std::vector<TextRenderer*> _textPool;
public:
    static std::vector<TextRenderer*> GetTextPool() {return _textPool;};
    std::string string;
    int charPerLine = 20; //x
    int lineLimit = 0; //y
    Vector2<int> position;
    TextRenderer(std::string text);
    ~TextRenderer();
};
};