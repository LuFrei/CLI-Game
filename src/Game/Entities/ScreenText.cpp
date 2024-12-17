#include "ScreenText.h"

ScreenText::ScreenText(CLGEngine::Vector2<int> position)
    : CLGEngine::Entity(position.x, position.y, 20, 1) // MAYDO: Require size on constructor
    , _text(new CLGEngine::TextRenderer(this, ""))
{ 

}


ScreenText::~ScreenText(){
    delete _text;
}

void ScreenText::SetText(std::string text){
    _text->SetText(text);
}