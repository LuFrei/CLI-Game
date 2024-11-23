#include "TextRenderer.h"


namespace CLGEngine{
std::vector<TextRenderer*> TextRenderer::_textPool;

TextRenderer::TextRenderer(std::string text)
    : string(text)
{
    _textPool.push_back(this);
}

TextRenderer::~TextRenderer(){
    auto it = std::find(
            _textPool.begin(),
            _textPool.end(),
            this
    );
    if(it != _textPool.end()) {
        _textPool.erase(it);
    }
}
};