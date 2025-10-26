#include "engine.hpp"
#include "model.hpp"
#include "texture.hpp"

#include <stdexcept>
#include <vector>

ogw::Engine::Engine(i32 width, i32 height, string title)
    : window(width, height, title)
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw runtime_error("Failed to initialize GLAD");
  glViewport(0, 0, width, height);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  PipelineCreateInfo pipelineInfo{};
  pipelineInfo.vertexPath = "base/shaders/shader.vert.spv";
  pipelineInfo.fragmentPath = "base/shaders/shader.frag.spv";
  pipelineInfo.spirv = true;

  pipeline = std::make_unique<Pipeline>(pipelineInfo);

  loadModels();
}

void ogw::Engine::run()
{
  pipeline->setup();
  ogwModel->bind();

  ogw::Texture::CreateInfo textureInfo{};
  textureInfo.filePath = "base/king.png";
  textureInfo.format = ogw::Texture::Format::RGBA;
  textureInfo.internalFormat = ogw::Texture::InternalFormat::RGB;
  textureInfo.magFilter = ogw::Texture::FilterMode::Nearest;
  textureInfo.minFilter = ogw::Texture::FilterMode::Nearest;
  textureInfo.mipLevel = 0;
  textureInfo.mipmapInterpolation = ogw::Texture::FilterMode::Nearest;
  textureInfo.wrapS = ogw::Texture::WrapMode::Repeat;
  textureInfo.wrapT = ogw::Texture::WrapMode::Repeat;

  ogw::Texture texture(textureInfo);
  texture.bind();

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  while (!window.shouldClose())
  {
    processInput();
    drawFrame();
  }
}

void ogw::Engine::loadModels()
{
  vector<ogw::Model::Vertex> vertices{
      {{-0.8f, -0.8f}, {0.7f, 0.7f, 0.7f}, {0.0f, 1.0f}},
      {{-1.0f, 1.0f}, {1, 1, 1}, {0.0f, 0.0f}},
      {{0.8f, 0.8f}, {0.8f, 0.8f, 0.8f}, {1.0f, 0.0f}},
      {{0.6f, -0.6f}, {0.6f, 0.6f, 0.6f}, {1.0f, 1.0f}},
  };

  vector<ogw::Model::Polygon> polygons{
      {0, 1, 2},
      {0, 2, 3},
  };

  ogwModel = std::make_unique<ogw::Model>(vertices, polygons);
}

void ogw::Engine::drawFrame() const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES, ogwModel->vertexCount(), GL_UNSIGNED_INT, 0);
  glfwSwapBuffers(window.get());
}

void ogw::Engine::processInput()
{
  if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.get(), true);
  glfwPollEvents();
}
