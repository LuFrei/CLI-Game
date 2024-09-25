#include "ScreenText.h"

ScreenText::ScreenText(CLGEngine::CORE::Vector2<int> position)
    : CLGEngine::Entity(position.x, position.y, 0, 0)
    , _text(new CLGEngine::TextRenderer(""))
{ 
    _text->position = position;
}


ScreenText::~ScreenText(){
    delete _text;
}

void ScreenText::SetText(std::string text){
    _text->string = text;
}