#pragma once

#include <string>

#include "rust_types.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

namespace ogw
{
  class Window
  {
  public:
    Window(i32 width, i32 height, string title);
    ~Window();

    Window(const Window &) = delete;
    Window &operator=(const Window &) = delete;

    bool shouldClose() const { return glfwWindowShouldClose(window); }
    GLFWwindow *get() const { return window; }

  private:
    void initGlfw();
    void spawn(i32 width, i32 height, string title, GLFWmonitor *monitor);
    void initGlad();

    GLFWwindow *window;
  };
}
