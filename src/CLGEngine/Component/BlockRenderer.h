#pragma once

#include "Render.h"

namespace CLGEngine {
    class BlockRenderer : public Renderer
    {
    private:
    public:
        BlockRenderer(CLGEngine::Entity* ent, CHAR_INFO& material);
        // ~BlockRenderer();
    };
    
}