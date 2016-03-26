#pragma once

#include "Texture.h"

namespace age {
    
    struct SpriteBatch {
        SpriteBatch(GLuint aNbIndices, unsigned int aIndicesOffset, const Texture* aTexture)
                : nbIndices(aNbIndices), indicesOffset(aIndicesOffset), texture(aTexture) {};
        ~SpriteBatch() {};
        
        GLuint nbIndices;
        GLuint indicesOffset;
        const Texture* texture;
    };
    
}