#version 150 core

in vec2 position;
in vec4 color;

out vec4 fragmentColor;

uniform float time;

void main() {
	gl_Position = vec4(position.xy, 0.0, 1.0);
	fragmentColor = color * 0.5 + vec4(1.0 * (cos(time) + 1.0) * 0.5,
								1.0 * (sin(time) + 1.0) * 0.5,
								1.0 * (cos(time) + 1.0) * 0.5, 0.0);
}
