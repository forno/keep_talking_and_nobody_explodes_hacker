#include "module/button.hpp"

#include <iostream>
#include <unordered_map>

#include <xmaho/input/input.hpp>

namespace
{

enum class Color
{
  Other,
  Blue,
  Red,
  White,
  Yellow,
};

enum class Label
{
  Other,
  Abort,
  Detonate,
  Hold,
};

enum class Instruction
{
  Click,
  ReleasingHeldButton,
};

void show_instruction(std::ostream& os, Instruction instruction)
{
  switch (instruction) {
  case Instruction::Click:
    os << "Click it!\n";
    return;
  case Instruction::ReleasingHeldButton:
    os << "-------------------------------------------\n"
          "Hold it! Refer to \"Releasing a Held Button\n"
          "  Blue strip  : 4 in countdown timer\n"
          "  Yellow strip: 5 in countdown timer\n"
          "  Other strip : 1 in countdown timer\n"
          "-------------------------------------------\n";
  }
}

}

void ktanehack::ButtonModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation& bomb)
{
  using xmaho::input::get_value;

  const std::unordered_map<int, Color> color_map{
    {0, Color::Blue},
    {1, Color::Red},
    {2, Color::White},
    {3, Color::Yellow},
  };
  const std::unordered_map<int, Label> label_map{
    {0, Label::Abort},
    {1, Label::Detonate},
    {2, Label::Hold},
  };

  os << "Please choice the button's COLOR\n"
        "  Blue  : 0\n"
        "  Red   : 1\n"
        "  White : 2\n"
        "  Yellow: 3\n"
        "  Other : 9\n";

  const auto color_it{color_map.find(get_value<int>(is))};
  const auto color{color_it != color_map.end() ? color_it->second : Color::Other};

  os << "Please choice the button's LABEL\n"
        "  Abort(中止)   : 0\n"
        "  Detonate(起爆): 1\n"
        "  Hold(長押し)  : 2\n"
        "  Other         : 9\n";

  const auto label_it{label_map.find(get_value<int>(is))};
  const auto label{label_it != label_map.end() ? label_it->second : Label::Other};

  if (color == Color::Blue && label == Label::Abort) {
    show_instruction(os, Instruction::ReleasingHeldButton);
    return;
  }

  if (label == Label::Detonate && (bomb.battery_count() >= 2)) {
    show_instruction(os, Instruction::Click);
    return;
  }

  if (color == Color::White && bomb.has_indicator("CAR")) {
    show_instruction(os, Instruction::ReleasingHeldButton);
    return;
  }

  if (bomb.battery_count() >= 3 && bomb.has_indicator("FRK")) {
    show_instruction(os, Instruction::Click);
    return;
  }

  if (color == Color::Yellow) {
    show_instruction(os, Instruction::ReleasingHeldButton);
    return;
  }

  if (color == Color::Red && label == Label::Hold) {
    show_instruction(os, Instruction::Click);
    return;
  }

  show_instruction(os, Instruction::ReleasingHeldButton);
}
