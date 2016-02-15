#pragma once

#include "Color.h"

struct Vertex {
	struct Position2D {
		float x;
		float y;
	} pos;
	Color color;
};