#version 330

out vec4 FragColor;

in vec3 OutColor;
in vec2 TexCoords

uniform sampler2D theTexture;

void main() {
  FragColor =  texture(theTexture, TexCoords);
}