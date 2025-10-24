#version 460 core
layout (location = 0) in vec2 inPosition;
layout (location = 3) in vec3 inColor;

layout (location = 0) out vec3 outColor;

void main() {
    gl_Position = vec4(inPosition.x * 3 / 4, inPosition.y, 0.0, 1.0);
    outColor = inColor;
}
