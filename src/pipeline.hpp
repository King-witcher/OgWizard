#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#include "rust_types.hpp"

using namespace std;

namespace ogw
{
  struct AttributeDescription
  {
    u32 location;
    i32 size;
    GLenum type;
    usize stride;
    usize offset;
  };

  struct PipelineCreateInfo
  {
    string vertexPath;
    string fragmentPath;
  };

  class Pipeline
  {
  public:
    Pipeline(string vertexPath, string fragmentPath);
    ~Pipeline();

    Pipeline(const Pipeline &) = delete;
    Pipeline &operator=(const Pipeline &) = delete;

    void setup() { glUseProgram(glProgramId); };

  private:
    void createShaderProgram(GLuint vertex, GLuint fragment);

    GLuint glProgramId;
  };
}
