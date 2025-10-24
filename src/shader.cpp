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

  i32 success;
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

  glVertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
  glFragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);
}

ShaderProgram::~ShaderProgram()
{
  glDeleteShader(glVertexShader);
}
