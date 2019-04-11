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

void ktanehack::WireModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation& bomb)
{
  using xmaho::input::get_value;

  switch (wire_count) {
  case 3:
    os << "No RED wire? true(1)/false(0)\n";
    if (get_value<bool>(is)) {
      os << "Cut: 2 (The second wire)\n";
      return;
    }
    os << "Is last WHITE? true(1)/false(0)\n";
    if (get_value<bool>(is)) {
      os << "Cut: Last wire (The third)\n";
      return;
    }
    os << "No BLUE wire? true(1)/false(0)\n";
    if (get_value<bool>(is)) {
      os << "Cut: Last wire (The third)";
      return;
    }
    os << "Cut: Last BLUE wire\n";
    return;
  default:
    os << "Error: Out of range\n";
  }
}
