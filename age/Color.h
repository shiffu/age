#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

namespace age {

    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
        
        Color() {
            r = g = b = a = 255;
        }
        
        Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
            r = _r;
            g = _g;
            b = _b;
            a = _a;
        }
    };

}