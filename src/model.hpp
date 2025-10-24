#include <glad/glad.h>
#include <vector>

#include "rust_types.hpp"
#include "engine.hpp"

namespace ogw
{
  class Model
  {
  public:
    struct Vertex
    {
      float position[2];
      float color[3];

      static std::vector<AttributeDescription> defaultAttributeDescriptions();
    };

    Model(const std::vector<Vertex> &verteices, const std::vector<u32> &indices);
    ~Model();

    Model &operator=(const Model &) = delete;
    Model(const Model &) = delete;

    void bind() const;

  private:
    u32 vao;
  };
}
