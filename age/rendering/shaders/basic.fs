#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 colorOut;
uniform sampler2D texSampler;

void main() {
    colorOut = texture(texSampler, fragmentUV) * fragmentColor;
}
