#ifndef KTANEHACK_MODULE_KEYPADS_HPP
#define KTANEHACK_MODULE_KEYPADS_HPP

#include "module.hpp"

namespace ktanehack
{

class KeypadsModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
