#pragma once

#include <string>
#include "export.h"
#include "Block.h"

/* stretch goal */
// We want to evaluate the size of the block based on the text
// support line breaks with plain "/" before line breaks and "/n"


/* 
For convenience, the block size is auto generated 
on construction to fit the text.

If the text is planned to be dynamic (changed frequently), 
Adjust the maximum block size manually using Resize(w, h)

Autosizing is not supported (yet, atleast).
*/

namespace clr{
class LIB_API TextBlock : public Block{
public:
    TextBlock(std::string text);
    TextBlock(std::string text, int widthLimit);
};
} // namespace clr