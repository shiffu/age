#version 150 core

in vec2 position;
in vec4 color;
in vec2 uv;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform float time;
uniform mat4 projection;

void main() {
	gl_Position = (projection * vec4(position.xy, 0.0, 1.0));
	fragmentColor = color * 0.3 + vec4(1.0 * (cos(time) + 1.0) * 0.5 * ((gl_Position.x + 1) * 0.5),
								1.0 * (sin(time) + 1.0) * 0.5 * ((gl_Position.y + 1) * 0.5),
								1.0 * (cos(time) + 1.0) * 0.5, 0.0);
	fragmentUV = uv;
}
