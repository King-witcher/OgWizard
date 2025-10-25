#include "pipeline.hpp"
#include "rust_types.hpp"

#include <fstream>
#include <filesystem>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;
using namespace ogw;

string readTextFile(const string &filepath)
{
  ifstream file(filepath, ios::binary);

  if (!file.is_open())
    throw runtime_error("Failed to open file: "s + filepath);

  usize size = filesystem::file_size(filepath);
  string content(size, '\0');
  file.read(content.data(), size);
  return content;
}

vector<u8> readBinaryFile(const string &filepath)
{
  ifstream file(filepath, ios::binary);
  if (!file.is_open())
    throw runtime_error("Failed to open file: "s + filepath);

  usize size = filesystem::file_size(filepath);
  vector<u8> data(size);
  if (size > 0)
  {
    file.read(reinterpret_cast<char *>(data.data()), static_cast<streamsize>(size));
    if (!file)
      throw runtime_error("Failed to read file: "s + filepath);
  }
  return data;
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
    throw runtime_error("ERROR::SHADER::COMPILATION_FAILED: "s + source + "\n" + infoLog);
  }

  return shaderId;
}

u32 specializeShader(vector<u8> source, GLenum type)
{
  u32 sid = glCreateShader(type);
  glShaderBinary(1, &sid, GL_SHADER_BINARY_FORMAT_SPIR_V, source.data(), source.size());
  glSpecializeShader(sid, "main", 0, nullptr, nullptr);

  i32 success;
  glGetShaderiv(sid, GL_SPIR_V_BINARY, &success);

  if (!success)
  {
    char infolog[512];
    glGetShaderInfoLog(sid, 512, nullptr, infolog);
    throw runtime_error("ERROR::SHADER::SPIRV::SPECIALIZATION_FAILED\n"s + infolog);
  }
  return sid;
}

Pipeline::Pipeline(PipelineCreateInfo createInfo)
{
  u32 vertex, fragment;

  if (createInfo.spirv)
  {
    auto vertexBin = readBinaryFile(createInfo.vertexPath);
    auto fragmentBin = readBinaryFile(createInfo.fragmentPath);

    vertex = specializeShader(vertexBin, GL_VERTEX_SHADER);
    fragment = specializeShader(fragmentBin, GL_FRAGMENT_SHADER);
  }
  else
  {
    auto vertexCode = readTextFile(createInfo.vertexPath);
    auto fragmentCode = readTextFile(createInfo.fragmentPath);

    vertex = compileShader(vertexCode, GL_VERTEX_SHADER);
    fragment = compileShader(fragmentCode, GL_FRAGMENT_SHADER);
  }

  createShaderProgram(vertex, fragment);
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

Pipeline::~Pipeline()
{
  glDeleteProgram(glProgramId);
}

void Pipeline::setup()
{
  glUseProgram(glProgramId);
}

void Pipeline::createShaderProgram(GLuint vertex, GLuint fragment)
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
