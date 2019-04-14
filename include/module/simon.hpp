#ifndef KTANEHACK_MODULE_SIMON_HPP
#define KTANEHACK_MODULE_SIMON_HPP

#include "module.hpp"

namespace ktanehack
{

class SimonModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
