#ifndef KTANEHACK_MODULE_BUTTON_HPP
#define KTANEHACK_MODULE_BUTTON_HPP

#include "module.hpp"

namespace ktanehack
{

class ButtonModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
