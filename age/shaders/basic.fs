#version 330 core

in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 colorOut;
uniform sampler2D fragTexture;

void main() {
	//vec4 texColor = texture(fragTexture, vec2(fragmentUV.x, 1.0 - fragmentUV.y));
    vec4 texColor = texture(fragTexture, fragmentUV);
    //colorOut = texColor * fragmentColor;
    //colorOut = vec4(texColor.g, 0, 0, 1);
    colorOut = texColor;
}
