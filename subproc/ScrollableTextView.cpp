#include "ScrollableTextView.h"

// TODO: Would be nice to be able to set custom position and size to logView
//      For now it's ahrd coded, but may need to add feature if the
//      Debugger is expanded.
ScrollableTextView::ScrollableTextView(clr::Screen* screen) 
: _screen(screen){
    for(int i = 0; i < SCREEN_HEIGHT; i++){
        _textLines[i].Resize(SCREEN_WIDTH/2, 1);
        _textLines[i].y = i;
        _textLines[i].Fill({' ',WHITE});
        _screen->AddToRenderQueue(&_textLines[i]);
    }
}

void ScrollableTextView::AddEntry(std::string log){
    _logHistory.push_back(log);

    if(_viewportOffset + SCREEN_HEIGHT < _logHistory.size() - 1){
        return;
    }else if(_viewportOffset + SCREEN_HEIGHT > _logHistory.size() - 1){
        int blockOffset = _viewportOffset % SCREEN_HEIGHT;
        int screenPosition = (_logHistory.size() - _viewportOffset - 1);
        _textLines[(blockOffset + screenPosition) % SCREEN_HEIGHT]
            .SetTextData(_logHistory.back());
    } else if(_viewportOffset + SCREEN_HEIGHT == _logHistory.size() - 1){
        ScrollDown();
    }
}

void ScrollableTextView::ScrollDown() {
    // Fun Fact: .size() is unsigned...
    if(_viewportOffset >= (int)(_logHistory.size() - 1)) {
        return;
    }
    _viewportOffset++;
    for(clr::Block& block : _textLines){
        block.y--;
        if(block.y < 0) {
            block.y = SCREEN_HEIGHT - 1;
            if(_viewportOffset + SCREEN_HEIGHT > _logHistory.size()){
                block.Fill({' ', WHITE});
            } else {
                block.SetTextData(_logHistory[_viewportOffset + SCREEN_HEIGHT - 1]);
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
            block.SetTextData(_logHistory[_viewportOffset]);
        }
    }
}