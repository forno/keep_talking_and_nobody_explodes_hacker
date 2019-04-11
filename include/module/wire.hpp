#ifndef KTANEHACK_MODULE_WIRE_HPP
#define KTANEHACK_MODULE_WIRE_HPP

#include "module.hpp"

namespace ktanehack
{

class WireModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
