#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "window.hpp"

int main()
{
  Window window(800, 600, "LearnOpenGL Window");

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    throw runtime_error("Failed to initialize GLAD");

  while (!window.shouldClose())
  {
    glfwPollEvents();
  }

  return 0;
}
