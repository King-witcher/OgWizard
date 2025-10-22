#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  auto window = glfwCreateWindow(800, 600, "OgWizard", nullptr, nullptr);

  if (!window)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  std::cin.get();

  return 0;
}
