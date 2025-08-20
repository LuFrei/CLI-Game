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
    std::vector<std::string> _logHistory;
    
    int _viewportOffset = 0;
    clr::Screen* _screen = nullptr;
public:
    ScrollableTextView(clr::Screen* screen);

    void AddEntry(std::string log);
    void ScrollDown();
    void ScrollUp();
};
