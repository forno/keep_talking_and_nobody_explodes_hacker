#ifndef KTANEHACK_MODULE_WIRE_HPP
#define KTANEHACK_MODULE_WIRE_HPP

#include "module.hpp"

namespace ktanehack
{

class WireModule
  : public Module
{
public:
  static void show_construct_message(std::ostream& os);

  WireModule(std::istream& is);

  void defuse(std::istream& is, std::ostream& os) override;
};

}

#endif
