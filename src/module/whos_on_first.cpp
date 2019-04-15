#include "module/whos_on_first.hpp"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <xmaho/input/input.hpp>

namespace
{

enum class DisplayWord
{
  Yes,
  First,
  Display,
  Okay,
  Says,
  Nothing,
  Empty,
  Blank,
  No,
  Led,
  Lead,
  Read,
  Red,
  Reed,
  Leed,
  HoldOn,
  You,
  YouAre,
  Your,
  YouRe,
  UR,
  There,
  TheyRe,
  Their,
  TheyAre,
  See,
  C,
  Cee
};

enum class Place
{
  LeftTop,
  LeftMiddle,
  LeftBottom,
  RightTop,
  RightMiddle,
  RightButtom
};

enum class ButtonWord
{
  Ready,
  First,
  No,
  Blank,
  Nothing,
  Yes,
  What,
  Uhhh,
  Left,
  Right,
  Middle,
  Okey,
  Wait,
  Press,
  You,
  YouAre,
  Your,
  YouRe,
  UR,
  U,
  UhUhh,
  UhUh,
  Whats,
  Done,
  Next,
  Hold,
  Sure,
  Like
};

std::string to_string(Place place)
{
  switch (place) {
    case Place::LeftTop:
      return "Left Top";
    case Place::LeftMiddle:
      return "Left Middle";
    case Place::LeftBottom:
      return "Left Bottom";
    case Place::RightTop:
      return "Right Top";
    case Place::RightMiddle:
      return "Right Middle";
    case Place::RightButtom:
      return "Right Bottom";
  }
  return "Out of range";
}

std::string to_string(ButtonWord button_word)
{
}

}

void ktanehack::WhosOnFirstModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation& bomb)
{
  using xmaho::input::get_value;

  const std::unordered_map<std::string, DisplayWord> display_map{
    {"yes", DisplayWord::Yes},
    {"sou", DisplayWord::Yes},
    {"そう", DisplayWord::Yes},
    {"first", DisplayWord::First},
    {"saisyo", DisplayWord::First},
    {"最初", DisplayWord::First},
    {"display", DisplayWord::Display},
    {"hyouji", DisplayWord::Display},
    {"表示", DisplayWord::Display},
    {"ok", DisplayWord::Okay},
    {"say", DisplayWord::Says},
    {"iu", DisplayWord::Says},
    {"言う", DisplayWord::Says},
    {"nothing", DisplayWord::Nothing},
    {"nai", DisplayWord::Nothing},
    {"何もない", DisplayWord::Nothing},
    {"e", DisplayWord::Empty},
    {"empty", DisplayWord::Empty},
    {"blank", DisplayWord::Blank},
    {"kara", DisplayWord::Blank},
    {"から", DisplayWord::Blank},
    {"no", DisplayWord::No},
    {"iya", DisplayWord::No},
    {"いや", DisplayWord::No},
    {"led", DisplayWord::Led},
    {"kaitou", DisplayWord::Led},
    {"解", DisplayWord::Led},
    {"lead", DisplayWord::Lead},
    {"kaisuu", DisplayWord::Lead},
    {"回", DisplayWord::Lead},
    {"read", DisplayWord::Read},
    {"kai", DisplayWord::Read},
    {"下位", DisplayWord::Read},
    {"red", DisplayWord::Red},
    {"kaikan", DisplayWord::Red},
    {"快", DisplayWord::Red},
    {"read", DisplayWord::Reed},
    {"hiraku", DisplayWord::Reed},
    {"開", DisplayWord::Reed},
    {"lead", DisplayWord::Leed},
    {"ato", DisplayWord::Leed},
    {"あと", DisplayWord::Leed},
    {"holdon", DisplayWord::HoldOn},
    {"matte", DisplayWord::HoldOn},
    {"mate", DisplayWord::HoldOn},
    {"まって", DisplayWord::HoldOn},
    {"you", DisplayWord::You},
    {"dou?", DisplayWord::You},
    {"どう?", DisplayWord::You},
    {"youare", DisplayWord::YouAre},
    {"mitibiku", DisplayWord::YouAre},
    {"導", DisplayWord::YouAre},
    {"your", DisplayWord::Your},
    {"onaji", DisplayWord::Your},
    {"同", DisplayWord::Your},
    {"youre", DisplayWord::YouRe},
    {"ugoku", DisplayWord::YouRe},
    {"動", DisplayWord::YouRe},
    {"ur", DisplayWord::UR},
    {"dou", DisplayWord::UR},
    {"どう", DisplayWord::UR},
    {"there", DisplayWord::There},
    {"taisyoujidai", DisplayWord::There},
    {"大正", DisplayWord::There},
    {"theyre", DisplayWord::TheyRe},
    {"taishouteki", DisplayWord::TheyRe},
    {"対照", DisplayWord::TheyRe},
    {"their", DisplayWord::Their},
    {"taisyousei", DisplayWord::Their},
    {"対称", DisplayWord::Their},
    {"theyare", DisplayWord::TheyAre},
    {"taisyou", DisplayWord::TheyAre},
    {"大賞", DisplayWord::TheyAre},
    {"see", DisplayWord::See},
    {"sainou", DisplayWord::See},
    {"才", DisplayWord::See},
    {"c", DisplayWord::C},
    {"saikai", DisplayWord::C},
    {"再", DisplayWord::C},
    {"cee", DisplayWord::Cee},
    {"saidai", DisplayWord::Cee},
    {"最", DisplayWord::Cee}
  };
  const std::unordered_map<DisplayWord, Place> place_map {
    {DisplayWord::Yes, Place::LeftMiddle},
    {DisplayWord::First, Place::RightTop},
    {DisplayWord::Display, Place::RightButtom},
    {DisplayWord::Okay, Place::RightTop},
    {DisplayWord::Says, Place::RightButtom},
    {DisplayWord::Nothing, Place::LeftMiddle},
    {DisplayWord::Empty, Place::LeftBottom},
    {DisplayWord::Blank, Place::RightMiddle},
    {DisplayWord::No, Place::RightButtom},
    {DisplayWord::Led, Place::LeftMiddle},
    {DisplayWord::Lead, Place::RightButtom},
    {DisplayWord::Read, Place::RightMiddle},
    {DisplayWord::Red, Place::RightMiddle},
    {DisplayWord::Reed, Place::LeftBottom},
    {DisplayWord::Leed, Place::LeftBottom},
    {DisplayWord::HoldOn, Place::RightButtom},
    {DisplayWord::You, Place::RightMiddle},
    {DisplayWord::YouAre, Place::RightButtom},
    {DisplayWord::Your, Place::RightMiddle},
    {DisplayWord::YouRe, Place::RightMiddle},
    {DisplayWord::UR, Place::LeftTop},
    {DisplayWord::There, Place::RightButtom},
    {DisplayWord::TheyRe, Place::LeftBottom},
    {DisplayWord::Their, Place::RightMiddle},
    {DisplayWord::TheyAre, Place::LeftMiddle},
    {DisplayWord::See, Place::RightButtom},
    {DisplayWord::C, Place::RightTop},
    {DisplayWord::Cee, Place::RightButtom}
  };
  const std::unordered_map<ButtonWord, std::vector<ButtonWord>> button_map{
    {ButtonWord::Ready, {ButtonWord::Yes, ButtonWord::Okey, ButtonWord::Middle, ButtonWord::Left, ButtonWord::Press, ButtonWord::Right, ButtonWord::Blank, ButtonWord::Ready}},
    {ButtonWord::First, {}},
    {ButtonWord::No, {}},
    {ButtonWord::Blank, {}},
    {ButtonWord::Nothing, {}},
    {ButtonWord::Yes, {}},
    {ButtonWord::What, {}},
    {ButtonWord::Uhhh, {}},
    {ButtonWord::Left, {}},
    {ButtonWord::Right, {}},
    {ButtonWord::Middle, {}},
    {ButtonWord::Okey, {}},
    {ButtonWord::Wait, {}},
    {ButtonWord::Press, {}},
    {ButtonWord::You, {}},
    {ButtonWord::YouAre, {}},
    {ButtonWord::Your, {}},
    {ButtonWord::YouRe, {}},
    {ButtonWord::UR, {}},
    {ButtonWord::U, {}},
    {ButtonWord::UhUhh, {}},
    {ButtonWord::UhUh, {}},
    {ButtonWord::Whats, {}},
    {ButtonWord::Done, {}},
    {ButtonWord::Next, {}},
    {ButtonWord::Hold, {}},
    {ButtonWord::Sure, {}},
    {ButtonWord::Like, {}}
  };

  while (true) {
    os << "What display?\n";
    if (const auto it{display_map.find(get_value<std::string>(is))}; it == display_map.end())
      break;
    else
      os << to_string(place_map.at(it->second)) << '\n';
  }
}
