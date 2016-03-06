#include "Utils.h"

#include <iostream>
#include <OpenGL/gl3.h>

namespace age {

    bool Utils::logGlErrors(const std::string& msg) {
        GLenum err = GL_NO_ERROR;
        bool hadErrors = false;
        
        while ((err = glGetError()) != GL_NO_ERROR) {
            std::cerr << msg << ": " << err << std::endl;
            hadErrors = true;
        }
        
        return hadErrors;
    }

}