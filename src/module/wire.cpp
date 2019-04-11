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
    os << "Does RED wire exist? true(1)/false(0)\n";
    if (!get_value<bool>(is)) {
      os << "Cut: 2(The second wire)\n";
      return;
    }

    os << "Is last WHITE? true(1)/false(0)\n";
    if (get_value<bool>(is)) {
      os << "Cut: Last wire (The third)\n";
      return;
    }

    os << "Does BLUE wire exist? true(1)/false(0)\n";
    if (get_value<bool>(is)) {
      os << "Cut: Last BLUE wire\n";
      return;
    }
    os << "Cut: Last wire (The third)";
    return;
  case 4:
    {
      os << "Please count RED wires\n";
      const auto red_count{get_value<int>(is)};
      if (red_count >= 2) {
        if (bomb.is_serial_last_value_odd()) {
          os << "Cut: Last RED wire\n";
          return;
        }
      }

      if (red_count == 0) {
        os << "Is last Yellow? true(1)/false(0)\n";
        if (get_value<bool>(is)) {
          os << "Cut: First wire\n";
          return;
        }
      }

      os << "Just one BLUE wires? true(1)/false(0)\n";
      if (get_value<bool>(is)) {
        os << "Cut: First wire\n";
        return;
      }

      os << "Count of YELLOW is over 1(2 <= YELLOW)? true(1)/false(0)\n";
      if (get_value<bool>(is)) {
        os << "Cut: Last wire\n";
        return;
      }
      os << "Cut: 2(The second wire)\n";
      return;
    }

  default:
    os << "Error: Out of range\n";
  }
}
