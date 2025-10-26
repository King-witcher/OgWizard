#include "model.hpp"

#include <vector>

using namespace std;
using namespace ogw;

vector<AttributeDescription> Model::Vertex::defaultAttributeDescriptions()
{
  auto stride = sizeof(Vertex);

  AttributeDescription vertexLocation{};
  vertexLocation.location = 0;
  vertexLocation.components = 2;
  vertexLocation.type = GL_FLOAT;
  vertexLocation.stride = stride;
  vertexLocation.offset = offsetof(Vertex, position);

  AttributeDescription vertexColor{};
  vertexColor.location = 1;
  vertexColor.components = 3;
  vertexColor.type = GL_FLOAT;
  vertexColor.stride = stride;
  vertexColor.offset = offsetof(Vertex, color);

  AttributeDescription vertexUV{};
  vertexUV.location = 2;
  vertexUV.components = 2;
  vertexUV.type = GL_FLOAT;
  vertexUV.stride = stride;
  vertexUV.offset = offsetof(Vertex, uv);

  return {vertexLocation, vertexColor, vertexUV};
}

Model::Model(const std::vector<Vertex> &vertices, const std::vector<Polygon> &polygons)
{
  vertexCount_ = polygons.size() * 3;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, polygons.size() * sizeof(Polygon), polygons.data(), GL_STATIC_DRAW);

  auto attribs = Vertex::defaultAttributeDescriptions();

  for (auto attrib : attribs)
  {
    glVertexAttribPointer(
        attrib.location,
        attrib.components,
        attrib.type,
        GL_FALSE,
        attrib.stride,
        (void *)attrib.offset);

    glEnableVertexAttribArray(attrib.location);
  }
}

Model::~Model()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
}
