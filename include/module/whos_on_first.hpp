#ifndef KTANEHACK_MODULE_WHOS_ON_FIRST_HPP
#define KTANEHACK_MODULE_WHOS_ON_FIRST_HPP

#include "module.hpp"

namespace ktanehack
{

class WhosOnFirstModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
