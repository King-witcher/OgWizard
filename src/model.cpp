#include "model.hpp"

#include <vector>

using namespace std;
using namespace ogw;

vector<AttributeDescription> Model::Vertex::defaultAttributeDescriptions()
{
  vector<AttributeDescription> attribDescription(2);
  attribDescription[0].location = 0;
  attribDescription[0].size = 2;
  attribDescription[0].type = GL_FLOAT;
  attribDescription[0].stride = sizeof(Vertex);
  attribDescription[0].offset = offsetof(Vertex, position);

  attribDescription[1].location = 3;
  attribDescription[1].size = 3;
  attribDescription[1].type = GL_FLOAT;
  attribDescription[1].stride = sizeof(Vertex);
  attribDescription[1].offset = offsetof(Vertex, color);

  return attribDescription;
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
    glVertexAttribPointer(attrib.location, attrib.size, attrib.type, GL_FALSE, attrib.stride, (void *)attrib.offset);
    glEnableVertexAttribArray(attrib.location);
  }
}

Model::~Model()
{
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
}
