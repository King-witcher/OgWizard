#include <glad/glad.h>
#include <vector>

#include "rust_types.hpp"

namespace ogw
{
  class Model
  {
  public:
    struct AttributeData
    {
      u32 location;
      u32 size;
      GLenum type;
      u32 stride;
      u32 offset;
    };

    struct Vertex
    {
      float position[3];
    };

    Model(const std::vector<Vertex> &verteices);
  };
}
