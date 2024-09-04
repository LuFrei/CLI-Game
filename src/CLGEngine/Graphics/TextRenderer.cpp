#include "TextRenderer.h"


namespace Graphics{
std::vector<TextRenderer*> TextRenderer::_textPool;

TextRenderer::TextRenderer(std::string text)
    : string(text)
{
    _textPool.push_back(this);
}

TextRenderer::~TextRenderer(){
    _textPool.erase(
        std::find(
            _textPool.begin(),
            _textPool.end(),
            this
    ));
}
};