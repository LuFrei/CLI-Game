#pragma once

#include "libclr.h"

#include <vector>
#include <string>

class ScrollableTextView{
private:
    std::array<clr::Block, SCREEN_HEIGHT> _textLines;
    std::vector<std:string> logHistory;
public:
    ScrollableTextView(int x, int y, int width, int height);

    // Do we want to link data set to display?
    void ScrollDown();
    void ScrollUp();
}
