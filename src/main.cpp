#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>

#include "window.hpp"
#include "shader.hpp"

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

  float vertices[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.0f, 0.5f, 0.0f};

  ShaderProgram shaderProgram("src/shaders/shader.vert", "src/shaders/shader.frag");

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window.get());
    processInput(window.get());
    glfwPollEvents();
  }

  return 0;
}
