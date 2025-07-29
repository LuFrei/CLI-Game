#define LIB_EXPORTS

#include "TextBlock.h"
#include <cmath>

namespace clr {

TextBlock::TextBlock(std::string text)
    : Block(1, text.size()){
    for(int i = 0; i < text.size(); i++){
        dataArr[i] = {(WCHAR)text[i], WHITE};
    }
}

TextBlock::TextBlock(std::string text, int widthLimit)
    : Block(0, 0, widthLimit, std::ceil(text.size()/widthLimit))
{
    
}
} // namespace clr
