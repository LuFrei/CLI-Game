#include "ScrollableTextView.h"

// TODO: Would be nice to be able to set custom position and size to logView
//      For now it's ahrd coded, but may need to add feature if the
//      Debugger is expanded.
ScrollableTextView::ScrollableTextView(clr::Screen* screen, int width, int height, int x, int y) 
: _screen(screen){
    for(int i = 0; i < height; i++){
        _textLines[i].Resize(width, 1);
        _textLines[i].x = x;
        _textLines[i].y = i + y;
        _textLines[i].Fill({' ',WHITE});
        _screen->AddToRenderQueue(&_textLines[i]);
    }
}

void ScrollableTextView::AddEntry(std::string log){
    _entries.push_back(log);

    if(_viewportOffset + SCREEN_HEIGHT < _entries.size() - 1){
        return;
    }else if(_viewportOffset + SCREEN_HEIGHT > _entries.size() - 1){
        int blockOffset = _viewportOffset % SCREEN_HEIGHT;
        int screenPosition = (_entries.size() - _viewportOffset - 1);
        _textLines[(blockOffset + screenPosition) % SCREEN_HEIGHT]
            .SetTextData(_entries.back());
    } else if(_viewportOffset + SCREEN_HEIGHT == _entries.size() - 1){
        ScrollDown();
    }
}

void ScrollableTextView::UpdateEntry(int i, std::string newMsg){
    if(_entries.size() <= i){
        AddEntry(newMsg);
    } else {
        _entries[i] = newMsg;
    }
}

void ScrollableTextView::ScrollDown() {
    // Fun Fact: .size() is unsigned...
    if(_viewportOffset >= (int)(_entries.size() - 1)) {
        return;
    }
    _viewportOffset++;
    for(clr::Block& block : _textLines){
        block.y--;
        if(block.y < 0) {
            block.y = SCREEN_HEIGHT - 1;
            if(_viewportOffset + SCREEN_HEIGHT > _entries.size()){
                block.Fill({' ', WHITE});
            } else {
                block.SetTextData(_entries[_viewportOffset + SCREEN_HEIGHT - 1]);
            }
        }
    }
}

void ScrollableTextView::ScrollUp() {
    if(_viewportOffset <= 0) return;
    
    _viewportOffset--;
    for(clr::Block& block : _textLines){
        block.y++;
        if(block.y >= SCREEN_HEIGHT) {
            block.y = 0;
            block.SetTextData(_entries[_viewportOffset]);
        }
    }
}