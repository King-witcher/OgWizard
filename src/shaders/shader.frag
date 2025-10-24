#version 460

layout (location = 0) in vec3 inColor;

out vec4 fragColor;

void main()
{
  fragColor = vec4(inColor, 1.0);
}
