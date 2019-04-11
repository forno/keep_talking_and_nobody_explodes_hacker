#include "module/wire.hpp"

#include <iostream>

#include <xmaho/input/input.hpp>

void ktanehack::WireModule::show_construct_message(std::ostream& os)
{
  os << "Please input wire count: \n";
}

ktanehack::WireModule::WireModule(std::istream& is)
  : wire_count{xmaho::input::get_value<int>(is)}
{
}

void ktanehack::WireModule::defuse(std::istream& is, std::ostream& os)
{
  os << "Wire count: " << wire_count << '\n';
}
