#include "Button.h"

#include <array>


const std::array<short, 5> CODE_COLORS= {
    FOREGROUND_RED,
    FOREGROUND_BLUE,
    FOREGROUND_GREEN,
    FOREGROUND_BLUE | FOREGROUND_RED,
    FOREGROUND_BLUE | FOREGROUND_GREEN
};

CHAR_INFO material = {
    '_',
    FOREGROUND_INTENSITY
};

Button::Button(std::vector<Door*> doors)
: CLGEngine::Entity({0, 0, 1, 1})
, _col(new CLGEngine::Collider(this)){
    int code = doors[0]->code();
    for(Door* door : doors){
        int doorCode = door->code();
        if(doorCode != code){
            throw;
        }
    }
    _col->isSolid = false;
    _doors = doors;
    _color = CODE_COLORS[code];
    material.Attributes |= CODE_COLORS[code];
    _rend = new CLGEngine::BlockRenderer(
        this, 
        material
    );
}

Button::~Button(){
    delete _col;
    delete _rend;
}

void Button::Activate(){
    for(Door* door : _doors){
        if(door->isOpen()){
            door->Close();
        } else {
            door->Open();
        }
    }
}

void Button::OnCollisionStart(CLGEngine::Entity* hit){
    Activate();
}