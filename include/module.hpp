#ifndef KTANEHACK_MODULE_HPP
#define KTANEHACK_MODULE_HPP

#include <iosfwd>

#include "bomb_information.hpp"

namespace ktanehack
{

class Module
{
public:
  virtual ~Module() = default;

  virtual void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) = 0;
};

}

#endif
