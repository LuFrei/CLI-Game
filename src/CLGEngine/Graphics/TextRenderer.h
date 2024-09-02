#pragma once

#include <string>

class TextRenderer{
private:
    std::string _string;
public:
    TextRenderer(std::string text);
    ~TextRenderer();
};