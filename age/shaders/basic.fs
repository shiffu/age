#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 colorOut;
uniform sampler2D texSampler;

void main() {
    //TODO: tmp, should use another uniform, or another shader when no texture is bound
    vec4 texColor = texture(texSampler, fragmentUV);
    if (texColor != vec4(0, 0, 0, 1.0)) {
        colorOut = texColor * fragmentColor;
    }
    else {
        colorOut = fragmentColor;
    }
}
