#pragma once

#include "Texture.h"

namespace age {
    
    struct SpriteBatch {
        SpriteBatch(GLuint aNbIndices, unsigned int aIndicesOffset, GLuint aTextureId)
                : nbIndices(aNbIndices), indicesOffset(aIndicesOffset), textureId(aTextureId) {};
        ~SpriteBatch() {};
        
        GLuint nbIndices;
        GLuint indicesOffset;
        GLuint textureId;
    };
    
}