#pragma once

#include "rust_types.hpp"
#include <glad/glad.h>

#include <stb_image.h>
#include <string>

namespace ogw
{
  class Texture
  {
  public:
    enum class InternalFormat
    {
      DepthComponent = GL_DEPTH_COMPONENT,
      DepthStencil = GL_DEPTH_STENCIL,
      Red = GL_RED,
      RG = GL_RG,
      RGB = GL_RGB,
      RGBA = GL_RGBA,
    };

    enum class Format
    {
      DepthComponent = GL_DEPTH_COMPONENT,
      DepthStencil = GL_DEPTH_STENCIL,
      Red = GL_RED,
      RG = GL_RG,
      RGB = GL_RGB,
      RGBA = GL_RGBA,
    };

    enum class WrapMode
    {
      Repeat = GL_REPEAT,
      MirroredRepeat = GL_MIRRORED_REPEAT,
      ClampToEdge = GL_CLAMP_TO_EDGE,
      ClampToBorder = GL_CLAMP_TO_BORDER,
    };

    enum class FilterMode
    {
      None = 0,
      Nearest = GL_NEAREST,
      Linear = GL_LINEAR,
    };

    struct CreateInfo
    {
      std::string filePath;
      Format format;
      InternalFormat internalFormat;
      i32 mipLevel = 0;
      WrapMode wrapS = WrapMode::Repeat;
      WrapMode wrapT = WrapMode::Repeat;
      FilterMode minFilter = FilterMode::Linear;
      FilterMode magFilter = FilterMode::Linear;
      /// @brief Mipmap interpolation filter mode. If set to NoFilter, mipmaps won't be generated.
      FilterMode mipmapInterpolation = FilterMode::None;
    };

    Texture(CreateInfo createInfo);
    ~Texture();

    void bind() const;
    u32 get() const { return glTextureID; }

  private:
    i32 width, height, nrChannels;
    u32 glTextureID;
  };
}
