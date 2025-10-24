#include "engine.hpp"
#include "model.hpp"

#include <stdexcept>
#include <vector>

ogw::Engine::Engine(i32 width, i32 height, string title)
    : window(width, height, title)
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw runtime_error("Failed to initialize GLAD");
  glViewport(0, 0, width, height);
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

  shaderProgram = std::make_unique<Pipeline>("src/shaders/shader.vert", "src/shaders/shader.frag");

  loadModels();
}

void ogw::Engine::run()
{
  shaderProgram->use();
  ogwModel->bind();
  while (!window.shouldClose())
  {
    processInput();
    drawFrame();
  }
}

void ogw::Engine::loadModels()
{
  vector<ogw::Model::Vertex> vertices = {
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
  };
  vector<u32> indices{
      0,
      1,
      3,
      1,
      2,
      3,
  };

  ogwModel = std::make_unique<ogw::Model>(vertices, indices);
}

void ogw::Engine::drawFrame() const
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawElements(GL_TRIANGLES, ogwModel->vertexCount(), GL_UNSIGNED_INT, 0);
  glfwSwapBuffers(window.get());
}

void ogw::Engine::processInput()
{
  if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.get(), true);
  glfwPollEvents();
}
