#include "shader.hpp"
#include "rust_types.hpp"

#include <fstream>
#include <vector>

using namespace std;

vector<char> readFile(string &filepath)
{
  ifstream file{filepath, ios::ate | ios::binary};

  if (!file.is_open())
    throw runtime_error("failed to open file: " + filepath);

  usize fileSize = static_cast<usize>(file.tellg());
  vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return vector<char>(10);
}

ShaderProgram::ShaderProgram(string vertexPath)
{
  auto vertexCode = readFile(vertexPath);
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
