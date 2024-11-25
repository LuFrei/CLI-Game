#include "TextRenderer.h"


namespace CLGEngine{

TextRenderer::TextRenderer(Entity* ent, std::string text)
: Renderer(ent) {
    SetText(text);
}

TextRenderer::~TextRenderer(){

}

void TextRenderer::SetText(std::string text){
    _text = text; 
    float capacity = block.rect.size.x * block.rect.size.y;
    float textSize = text.size();
    if(textSize < capacity){
        capacity = text.size();
    } else {
        // TODO: Notify user the text will be cut off
        //       IF autoSize is off.
    }

    if(capacity == 0) return;

    // Full Text Wrap, cut off on limit
    for(int i = 0; i < capacity; i++){
        block.dataArr[i].Char.AsciiChar = text[i];
    }
}
};