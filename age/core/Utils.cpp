#include "Utils.h"

#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

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