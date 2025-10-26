#pragma once

#include <glad/glad.h>
#include <vector>

#include "rust_types.hpp"
#include "pipeline.hpp"

namespace ogw
{
  class Model
  {
  public:
    struct Vertex
    {
      f32 position[2];
      f32 color[3];
      f32 uv[2];

      static std::vector<AttributeDescription> defaultAttributeDescriptions();
    };

    struct Polygon
    {
      u32 v1;
      u32 v2;
      u32 v3;
    };

    Model(const std::vector<Vertex> &vertices, const std::vector<Polygon> &polygons);
    ~Model();

    Model &operator=(const Model &) = delete;
    Model(const Model &) = delete;

    void bind() const { glBindVertexArray(vao); }
    usize vertexCount() const { return vertexCount_; };

  private:
    u32 vbo, ebo, vao;
    usize vertexCount_;
  };
}
