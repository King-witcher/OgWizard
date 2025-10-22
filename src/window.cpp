#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

Window::Window(i32 width, i32 height, string title)
{
  initGlfw();
  spawnWindow(width, height, title);
}

Window::~Window()
{
  glfwDestroyWindow(window);
  glfwTerminate();
}

void Window::initGlfw()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::spawnWindow(i32 width, i32 height, string title)
{
  window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!window)
  {
    glfwTerminate();
    throw runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
}
