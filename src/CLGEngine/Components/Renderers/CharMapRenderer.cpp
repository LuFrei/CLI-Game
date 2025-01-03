#include "CharMapRenderer.h"

namespace CLGEngine {

CharMapRenderer::CharMapRenderer(Entity* ent, TileMap& charMap)
: CharMapRenderer(ent, charMap, false) {
}

CharMapRenderer::CharMapRenderer(Entity* ent, TileMap& charMap, bool isSquare)
: Renderer(ent){
    SetSquareCells(isSquare);
	SetCharMap(charMap);
}

// ! Block is set to 0,0 0,0 cuz of entity!
// For THIS, we will set the block based on charMap size
void CharMapRenderer::SetCharMap(TileMap& charMap){
	// TODO: IU really really really hate this. We need a bmore elegant way to do Square cells maybe higher in the chain..
	int width = _squareCells ? charMap.size.x * 2 : charMap.size.x;
	float xPos =  _squareCells ? charMap.offset.x * 2 : charMap.offset.x;
	block.SetRect({{xPos, (float)charMap.offset.y}, {(float)width, (float)charMap.size.y}});
	int idx = 0;
    for(int y = charMap.offset.y; y < charMap.size.y + charMap.offset.y; y++){
		for(int x = charMap.offset.x; x < charMap.size.x + charMap.offset.x; x++){
			int xCell = x;
			if (this->_squareCells) {
				xCell *= 2;
			}
			wchar_t character = charMap.GetTile({x, y});
			if (this->_squareCells) {
				block.dataArr[idx] = charMap.definitions[character];
				block.dataArr[idx +1] = charMap.definitions[character];
			} else {
				block.dataArr[idx] = charMap.definitions[character];
			}
            idx = _squareCells ? idx + 2 : idx + 1;
		}
	}
}
}