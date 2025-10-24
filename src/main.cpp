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

  u32 VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  u32 VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);

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
