#pragma once

#include <glad/glad.h>

#include <vector>
#include <string>

using namespace std;

class ShaderProgram
{
public:
  ShaderProgram(string vertexPath, string fragmentPath);
  ~ShaderProgram();

  ShaderProgram(const ShaderProgram &) = delete;
  ShaderProgram &operator=(const ShaderProgram &) = delete;

  void use();

private:
  void createProgram(GLuint vertex, GLuint fragment);

  GLuint glProgramId;
};
