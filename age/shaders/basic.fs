#version 150 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;
uniform sampler2D fragTexture;

void main() {
	vec4 texColor = texture(fragTexture, fragmentUV);
	color = texColor * fragmentColor;
}
