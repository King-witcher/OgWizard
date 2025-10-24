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

GLuint compileShader()
{
}

ShaderProgram::ShaderProgram(string vertexPath)
{
  auto vertexCode = readFile(vertexPath);
  std::cout << vertexCode << std::endl;
  glVertexShader = glCreateShader(GL_VERTEX_SHADER);
  auto codePtr = vertexCode.data();
  glShaderSource(glVertexShader, 1, &codePtr, nullptr);
  glCompileShader(glVertexShader);

  i32 success;
  glGetShaderiv(glVertexShader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(glVertexShader, 512, nullptr, infoLog);
    throw runtime_error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"s + infoLog);
  }
}

ShaderProgram::~ShaderProgram()
{
  glDeleteShader(glVertexShader);
}
