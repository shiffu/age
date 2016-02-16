#pragma once

#include "Color.h"

struct Position2D {
	float x;
	float y;
};

struct UV {
	float u;
	float v;
};

struct Vertex {
	Position2D pos;
	Color color;
	UV uv;
};