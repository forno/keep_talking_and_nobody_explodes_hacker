#include "module/simon.hpp"

#include <iostream>
#include <unordered_map>

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
}
