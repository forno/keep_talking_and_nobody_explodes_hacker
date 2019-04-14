#include "module/simon.hpp"

#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>

#include <xmaho/input/input.hpp>

namespace
{

enum class Color
{
  Red,
  Blue,
  Green,
  Yellow
};

std::string to_string(Color color)
{
  switch (color) {
  case Color::Red:
    return "Red";
  case Color::Blue:
    return "Blue";
  case Color::Green:
    return "Ggreen";
  case Color::Yellow:
    return "Yellow";
  }
  return "Out of range";
}

}

void ktanehack::SimonModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation& bomb)
{
  using xmaho::input::get_value;

  const std::unordered_map<bool, std::unordered_map<int, std::unordered_map<Color, Color>>> color_map{
    {true, {
      {0, {
        {Color::Red,    Color::Blue},
        {Color::Blue,   Color::Red},
        {Color::Green,  Color::Yellow},
        {Color::Yellow, Color::Green}
      }},
      {1, {
        {Color::Red,    Color::Yellow},
        {Color::Blue,   Color::Green},
        {Color::Green,  Color::Blue},
        {Color::Yellow, Color::Red}
      }},
      {2, {
        {Color::Red,    Color::Green},
        {Color::Blue,   Color::Red},
        {Color::Green,  Color::Yellow},
        {Color::Yellow, Color::Blue}
      }}
    }},
    {false, {
      {0, {
        {Color::Red,    Color::Blue},
        {Color::Blue,   Color::Yellow},
        {Color::Green,  Color::Green},
        {Color::Yellow, Color::Red}
      }},
      {1, {
        {Color::Red,    Color::Red},
        {Color::Blue,   Color::Blue},
        {Color::Green,  Color::Yellow},
        {Color::Yellow, Color::Green}
      }},
      {2, {
        {Color::Red,    Color::Yellow},
        {Color::Blue,   Color::Green},
        {Color::Green,  Color::Blue},
        {Color::Yellow, Color::Red}
      }}
    }}
  };
  const std::unordered_map<std::string, Color> input_map{
    {"r", Color::Red},
    {"red", Color::Red},
    {"b", Color::Blue},
    {"blue", Color::Blue},
    {"g", Color::Green},
    {"green", Color::Green},
    {"y", Color::Yellow},
    {"yellow", Color::Yellow}
  };

  const auto& current_table{color_map.at(bomb.is_serial_containing_vowel())};

  os << "How much strikes?\n";
  const auto strike_count{get_value<int>(is)};

  std::vector<Color> colors{};
  while (true) {
    os << "-------------------------\n"
          "Please select LAST COLOR or now STRIKE\n"
          "  Red:    r/red\n"
          "  Bule:   b/bule\n"
          "  Green:  g/green\n"
          "  Yellow: y/yellow\n"
          "  Strike Numbers: 0/1/2\n"
          "  FINISH: f/finish\n";

    const auto input{get_value<std::string>(is)};
    const auto it{input_map.find(input)};
    if (it == input_map.end())
      break;

    colors.push_back(it->second);
    os << "---------------\n";
    const auto& specific_map{current_table.at(strike_count)};
    for (const auto& e : colors)
      os << to_string(specific_map.at(e)) << '\n';
  }
}
