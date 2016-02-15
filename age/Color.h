#pragma once

#include <GL/glew.h>

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