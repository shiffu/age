#version 330 core

in vec2 position;
in vec4 color;
in vec2 uv;

out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 projection;

void main() {
	gl_Position = (projection * vec4(position.xy, 0.0, 1.0));
    
	fragmentColor = color;

    fragmentUV = uv;
}
