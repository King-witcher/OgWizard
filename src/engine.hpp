#pragma once

#include "rust_types.hpp"
#include "window.hpp"
#include "model.hpp"
#include "pipeline.hpp"

#include <glad/glad.h>
#include <memory>

namespace ogw
{
  class Engine
  {
  public:
    Engine(i32 width, i32 height, string title);

    void run();

  private:
    void loadModels();
    void drawFrame() const;
    void processInput();

    std::unique_ptr<ogw::Model> ogwModel;
    std::unique_ptr<Pipeline> pipeline;
    ogw::Window window;
  };
}
