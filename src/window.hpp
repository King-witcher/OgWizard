#pragma once

#include <string>
#include "rust_types.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

class Window
{
public:
  Window(i32 width, i32 height, string title);
  ~Window();

  Window(const Window &) = delete;
  Window &operator=(const Window &) = delete;

  bool shouldClose() { return glfwWindowShouldClose(window); }

private:
  void initGlfw();
  void spawnWindow(i32 width, i32 height, string title);
  void initGlad();

  GLFWwindow *window;
};
