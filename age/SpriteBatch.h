#pragma once

#include "Texture.h"

namespace age {
    
    struct SpriteBatch {
        SpriteBatch(GLuint aOffset, GLuint aNumVertices, const Texture& aTexture)
                : offset(aOffset), numVertices(aNumVertices), texture(aTexture) {};
        ~SpriteBatch() {};
        
        GLuint offset;
        GLuint numVertices;
        Texture texture;
    };
    
}