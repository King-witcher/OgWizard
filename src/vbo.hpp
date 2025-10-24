#pragma once

#include <glad/glad.h>
#include <vector>

using namespace std;

class VBO
{
public:
  VBO(const vector<float> &vertices);
  ~VBO();

  VBO(const VBO &) = delete;
  VBO &operator=(const VBO &) = delete;

  void bind() const;
  void unbind() const;

private:
  GLuint bufferId;
};
