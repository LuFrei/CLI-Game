#pragma once

#include "Renderer.h"

namespace CLGEngine {
    class BlockRenderer : public Renderer
    {
    private:
    public:
        BlockRenderer(CLGEngine::Entity* ent, CHAR_INFO& material);
        BlockRenderer(CLGEngine::Entity* ent, CHAR_INFO& material, bool isSquare);

        // ~BlockRenderer();
        // TODO: make Resize func
    };
    
}