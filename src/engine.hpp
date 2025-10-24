#include "rust_types.hpp"

#include <glad/glad.h>

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
}
