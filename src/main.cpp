#include <cstdlib>
#include <iostream>

#include "bomb_information.hpp"
#include "ktanehack.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
  ktanehack::BombInformation bomb{std::cin, std::cout};

  while (auto module{ktanehack::get_module(std::cin, std::cout)})
    module->defuse(std::cin, std::cout, bomb);

  std::cout << "Thanks play Keep Talking and Nobody Explodes!\n";
  return EXIT_SUCCESS;
}
