#version 330

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoords;

out vec2 TexCoords;
out vec3 OutColor;

uniform vec2 xyOffset;

void main() {
  vec3 calcPosition = inPosition + vec3(xyOffset, 0.0f);
  gl_Position = vec4(calcPosition, 1.0f);
  OutColor = inColor;
  TexCoords = inTexCoords;
}