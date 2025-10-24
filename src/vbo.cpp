#include "vbo.hpp"

VBO::VBO(const vector<float> &vertices)
{
  glGenBuffers(1, &bufferId);
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

VBO::~VBO()
{
  glDeleteBuffers(1, &bufferId);
}

void VBO::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, bufferId);
}
