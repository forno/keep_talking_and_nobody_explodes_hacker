#include "module/wire.hpp"

#include <iostream>

void ktanehack::WireModule::show_construct_message(std::ostream& os)
{
  os << "Please input wire count: \n";
}

ktanehack::WireModule::WireModule(std::istream& is)
{
}

void ktanehack::WireModule::defuse(std::istream& is, std::ostream& os)
{
  os << "NICE defused\n";
}
