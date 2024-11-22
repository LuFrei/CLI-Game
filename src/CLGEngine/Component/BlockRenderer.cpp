#include "BlockRenderer.h"

namespace CLGEngine{
BlockRenderer::BlockRenderer(CLGEngine::Entity* ent, CHAR_INFO& material)
: Renderer(ent) {
    int dataSize = block.rect.size.x * block.rect.size.y;
    for (int i = 0; i < dataSize; i++){
        block.dataArr[i] = material;
    }
}
}