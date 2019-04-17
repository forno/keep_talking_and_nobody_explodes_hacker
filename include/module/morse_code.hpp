#ifndef KTANEHACK_MODULE_MORSE_CODE_HPP
#define KTANEHACK_MODULE_MORSE_CODE_HPP

#include "module.hpp"

namespace ktanehack
{

class MorseCodeModule
  : public Module
{
public:
  void defuse(std::istream& is, std::ostream& os, BombInformation& bomb) override;
};

}

#endif
