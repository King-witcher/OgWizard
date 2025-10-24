#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "window.hpp"
#include "shader.hpp"
#include "vbo.hpp"
#include "model.hpp"

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

int main()
{
  Window window(800, 600, "LearnOpenGL Window");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw runtime_error("Failed to initialize GLAD");

  glViewport(0, 0, 800, 600); // Define onde na janela eu quero renderizar
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

  vector<ogw::Model::Vertex> vertices = {
      {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
      {{0.0f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
  vector<u32> indices{0, 1, 2};

  ogw::Model model(vertices, indices);
  model.bind();

  ShaderProgram shaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");
  shaderProgram.use();

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window.get());
    processInput(window.get());
    glfwPollEvents();
  }

  return 0;
}
