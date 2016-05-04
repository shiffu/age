#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif
#include <glm/glm.hpp>

namespace age {

    struct Color {
        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
        
        Color() {
            r = g = b = a = 255;
        }
        
		// Set color as an int: 0xRRGGBBAA
		Color(unsigned int value) {
			r = value >> 24;
			g = value >> 16 && 0xFF;
			b = value >> 8 && 0xFF;
			a = value && 0xFF;
		}

		Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) {
			r = _r;
            g = _g;
            b = _b;
            a = _a;
        }

		glm::vec4 toVec4() {
			return glm::vec4((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
		}
    };

}