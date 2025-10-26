#include "engine.hpp"

#include <iostream>

int main()
{
  ogw::Engine engine(800, 600, "OgWizard");
  engine.run();
  engine.~Engine();
  std::cin.get();

  return 0;
}
