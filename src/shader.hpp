#pragma once

#include <glad/glad.h>

#include <vector>
#include <string>

class ShaderProgram
{
public:
  ShaderProgram(std::string vertexPath);
  ~ShaderProgram();

  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram &operator=(const ShaderProgram &) = delete;

private:
  GLuint glVertexShader;
};
