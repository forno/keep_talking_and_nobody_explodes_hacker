#include <cstdlib>
#include <iostream>

#include "ktanehack.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  ktanehack::show_modules(std::cout);
  while (auto module{ktanehack::get_module(std::cin, std::cout)}) {
    module->defuse(std::cin, std::cout);
    ktanehack::show_modules(std::cout);
  }

  std::cout << "Thanks play Keep Talking and Nobody Explodes!\n";
  return EXIT_SUCCESS;
}
