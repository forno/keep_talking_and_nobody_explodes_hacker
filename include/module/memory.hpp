#ifndef KTANEHACK_MODULE_MEMORY_HPP
#define KTANEHACK_MODULE_MEMORY_HPP

#include "module.hpp"

namespace ktanehack
{

class MemoryModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
