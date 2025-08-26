#pragma once

#include "libclr.h"

#include <vector>
#include <array>
#include <string>

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
/* 
Scrolling only works when _textList is larger than _textLines

window is a range of 
Should log histroy be in or out of the class?

*/

class ScrollableTextView{
private:
    std::array<clr::Block, SCREEN_HEIGHT> _textLines;
    std::vector<std::string> _entries;
    
    int _viewportOffset = 0;
    clr::Screen* _screen = nullptr;
public:
    ScrollableTextView(clr::Screen* screen, int width, int height, int x, int y);

    void AddEntry(std::string log);
    void UpdateEntry(int i, std::string newMsg);
    void ScrollDown();
    void ScrollUp();

    std::string* GetEntry(int i){
        if(i > _entries.size()){
            _entries.resize(i);
        }
        return &_entries[i];
    }
};
