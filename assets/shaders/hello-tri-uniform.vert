#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 customColor;

uniform vec2 offset;

void main() {
  vec3 calcPos = aPos + vec3(offset, 1.0f);
  gl_Position = vec4(calcPos, 1.0);
  customColor = aColor;
}