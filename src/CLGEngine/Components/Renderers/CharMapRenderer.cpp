#include "CharMapRenderer.h"

namespace CLGEngine {

CharMapRenderer::CharMapRenderer(Entity* ent, TileMap& charMap)
: CharMapRenderer(ent, charMap, false) {
}

CharMapRenderer::CharMapRenderer(Entity* ent, TileMap& charMap, bool isSquare)
: Renderer(ent) {
    SetSquareCells(isSquare);
    int idx = 0;
    for(int y = charMap.offset.y; y < charMap.size.y + charMap.offset.y; y++){
		for(int x = charMap.offset.x; x < charMap.size.x + charMap.offset.x; x++){
			int xCell = x;
			if (this->_squareCells) {
				xCell *= 2;
			}
			// check over flow
			// if(xCell >= _width || y >= _height){
			// 	continue;
			// }
			wchar_t character = charMap.GetTile({(float)x, (float)y});
			// int idx = _width * y + xCell;
			if(character == '#'){
				unsigned short whiteBG = BACKGROUND_GREEN 
										 | BACKGROUND_BLUE 
										 | BACKGROUND_RED 
										 | BACKGROUND_INTENSITY;
				if (this->_squareCells) {
					block.dataArr[idx] = {' ', whiteBG};
					block.dataArr[idx +1] = {' ', whiteBG};
				} else {
					block.dataArr[idx] = {' ', whiteBG};
				}
			} else if (character == '*' || character == 'e'){
				unsigned short yellowBG = BACKGROUND_GREEN | BACKGROUND_RED;
				if (this->_squareCells) {
					block.dataArr[idx] = {' ', yellowBG};
					block.dataArr[idx +1] = {' ', yellowBG};
				} else {
					block.dataArr[idx] = {' ', yellowBG};
				}
			}

            idx++;
		}
	}
}

}