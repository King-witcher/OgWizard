#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

using namespace ogw;

Window::Window(i32 width, i32 height, string title)
{
  initGlfw();

  i32 monitorCount;
  GLFWmonitor **monitors = glfwGetMonitors(&monitorCount);
  GLFWmonitor *monitor;
  if (monitorCount > 1)
    monitor = monitors[1];
  else
    monitor = monitors[0];

  spawn(width, height, title, monitor);
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
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void Window::spawn(i32 width, i32 height, string title, GLFWmonitor *monitor)
{
  window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
  glfwSetWindowPos(window, -1000, 200);
  if (!window)
  {
    glfwTerminate();
    throw runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(window);
}
