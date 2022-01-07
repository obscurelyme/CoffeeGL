#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoords;

uniform vec2 xOffset;

void main() { gl_Position = vec4(inPosition, 1.0f); }