#define LIB_EXPORTS

#include "TextBlock.h"
#include <cmath>

namespace clr {

TextBlock::TextBlock(std::string text)
    : Block(text.size(), 1){
    for(int i = 0; i < text.size(); i++){
        dataArr[i] = {(WCHAR)text[i], WHITE};
    }
}

} // namespace clr
