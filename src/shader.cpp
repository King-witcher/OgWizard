#include "shader.hpp"
#include "rust_types.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

string readFile(const string &filepath)
{
  ifstream file(filepath, ios::binary);

  if (!file.is_open())
    throw runtime_error("Failed to open file: "s + filepath);

  usize size = filesystem::file_size(filepath);
  string content(size, '\0');
  file.read(content.data(), size);
  return content;
}

GLuint compileShader(string source, GLenum type)
{
  GLuint shaderId = glCreateShader(type);
  auto ptr = source.data();
  glShaderSource(shaderId, 1, &ptr, nullptr);
  glCompileShader(shaderId);

  GLint success;
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
    throw runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"s + infoLog);
  }

  return shaderId;
}

ShaderProgram::ShaderProgram(string vertexPath, string fragmentPath)
{
  auto vertexCode = readFile(vertexPath);
  auto fragmentCode = readFile(fragmentPath);

  GLuint vertex = compileShader(vertexCode, GL_VERTEX_SHADER);
  GLuint fragment = compileShader(fragmentCode, GL_FRAGMENT_SHADER);

  createProgram(vertex, fragment);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

ShaderProgram::~ShaderProgram()
{
  glDeleteProgram(glProgramId);
}

void ShaderProgram::use()
{
  glUseProgram(glProgramId);
}

void ShaderProgram::createProgram(GLuint vertex, GLuint fragment)
{
  glProgramId = glCreateProgram();
  glAttachShader(glProgramId, vertex);
  glAttachShader(glProgramId, fragment);
  glLinkProgram(glProgramId);

  GLint success;
  glGetProgramiv(glProgramId, GL_LINK_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetProgramInfoLog(glProgramId, 512, nullptr, infoLog);
    throw runtime_error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n"s + infoLog);
  }
}
