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
    float capacity = entity->rect().size.x * entity->rect().size.y;

    if(text.size() < capacity){
        capacity = text.size();
        block.Resize((int)capacity, 1); // TODO: calculate y
    } else {
        // TODO: Notify user the text will be cut off
        //       IF autoSize is off.
    }

    block.dataArr.clear();
    // Full Text Wrap, cut off on limit
    for(int i = 0; i < capacity; i++){
        block.dataArr.push_back({(WCHAR)text[i], WHITE});
    }
}
};