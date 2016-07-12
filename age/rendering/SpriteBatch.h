#pragma once

#include "Texture.h"

namespace age {
    
    struct SpriteBatch {

        SpriteBatch(GLuint aCount, GLuint aOffset, GLuint aTextureId)
                : count(aCount), offset(aOffset), textureId(aTextureId) {};
                
        GLuint count = 0;
        GLuint offset = 0;
        GLuint textureId = 0;
    };
    
}