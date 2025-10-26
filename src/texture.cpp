#include "texture.hpp"

#include <stdexcept>

using namespace ogw;

Texture::Texture(CreateInfo createInfo)
{
  if (createInfo.magFilter == FilterMode::None || createInfo.minFilter == FilterMode::None)
    throw std::runtime_error("MagFilter and MinFilter cannot be set to NoFilter.");

  unsigned char *data = stbi_load(createInfo.filePath.c_str(), &width, &height, &nrChannels, 0);
  if (!data)
    throw std::runtime_error("Failed to load texture: " + createInfo.filePath);

  glGenTextures(1, &glTextureID);
  glBindTexture(GL_TEXTURE_2D, glTextureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (i32)createInfo.wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (i32)createInfo.wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (i32)createInfo.magFilter);

  if (createInfo.mipmapInterpolation == FilterMode::None) // No mipmap
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (i32)createInfo.minFilter);
  else if (createInfo.mipmapInterpolation == FilterMode::Nearest) // Nearest mipmap
  {
    if (createInfo.minFilter == FilterMode::Nearest) // Nearest minification + nearest mipmap
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    else // Linear minification + nearest mipmap
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
  }
  else // Linear mipmap
  {
    if (createInfo.minFilter == FilterMode::Nearest) // Nearest minification + linear mipmap
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    else // Linear minification + linear mipmap
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  }

  glTexImage2D(
      GL_TEXTURE_2D,
      createInfo.mipLevel,
      (i32)createInfo.internalFormat,
      width,
      height,
      0,
      (i32)createInfo.format,
      GL_UNSIGNED_BYTE,
      data);

  if (createInfo.mipmapInterpolation != FilterMode::None)
    glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Texture::~Texture()
{
  glDeleteTextures(1, &glTextureID);
}

void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, glTextureID);
}
