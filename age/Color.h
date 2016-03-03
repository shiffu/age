#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

namespace age {

    struct RGBAColor {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };
    
    union Color {
        RGBAColor rgba;
        GLuint value;
    };

}