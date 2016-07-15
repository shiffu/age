#pragma once

#include "Texture.h"

namespace age {
    
    struct SpriteBatch {

        SpriteBatch(GLuint aCount, GLuint aOffset, GLuint aTextureId, GLenum aPrimitive)
                : count(aCount), offset(aOffset), textureId(aTextureId), primitive(aPrimitive) {};
                
        GLuint count;
        GLuint offset;
        GLuint textureId;
        GLenum primitive;
    };
    
}