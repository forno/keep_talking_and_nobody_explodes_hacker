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
  Okay,
  Wait,
  Press,
  You,
  YouAre,
  Your,
  YouRe,
  UR,
  U,
  UhHuh,
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
  switch (button_word) {
  case ButtonWord::Ready:
    return "準備OK";
  case ButtonWord::First:
    return "最初";
  case ButtonWord::No:
    return "違う";
  case ButtonWord::Blank:
    return "ブランク";
  case ButtonWord::Nothing:
    return "なし";
  case ButtonWord::Yes:
    return "そう";
  case ButtonWord::What:
    return "何？";
  case ButtonWord::Uhhh:
    return "えーと";
  case ButtonWord::Left:
    return "残り";
  case ButtonWord::Right:
    return "右";
  case ButtonWord::Middle:
    return "真ん中";
  case ButtonWord::Okay:
    return "オーケー";
  case ButtonWord::Wait:
    return "ウェイト";
  case ButtonWord::Press:
    return "押して";
  case ButtonWord::You:
    return "どう？";
  case ButtonWord::YouAre:
    return "導";
  case ButtonWord::Your:
    return "同";
  case ButtonWord::YouRe:
    return "動";
  case ButtonWord::UR:
    return "左";
  case ButtonWord::U:
    return "それ";
  case ButtonWord::UhHuh:
    return "うんうん";
  case ButtonWord::UhUh:
    return "そうそう";
  case ButtonWord::Whats:
    return "え？";
  case ButtonWord::Done:
    return "できた";
  case ButtonWord::Next:
    return "次";
  case ButtonWord::Hold:
    return "まって";
  case ButtonWord::Sure:
    return "もちろん";
  case ButtonWord::Like:
    return "例えば";
  }
  return "Out of range";
}

void show_display_information(std::ostream& os) {
    os << 
      "そう     : sou / yes\n"
      "最初     : saisyo / first\n"
      "表示     : hyouji / display\n"
      "言う     : iu / say\n"
      "オーケー : ok\n"
      "何もない : nai / nothing\n"
      "         : e / empty\n"
      "から     : kara / blank\n"
      "いや     : iya / no\n"
      "解       : kaitou / led\n"
      "回       : kaisuu / lead\n"
      "下位     : kai / read\n"
      "快       : kaikan / red\n"
      "開       : hiraku / read\n"
      "あと     : ato / lead\n"
      "まって   : mate / matte / holdon\n"
      "どう?    : dou? / you\n"
      "導       : mitibiku / youare\n"
      "同       : onaji / your\n"
      "動       : ugoku / youre\n"
      "どう     : dou / ur\n"
      "大正     : taisyoujidai / there\n"
      "対照     : taishouteki / theyre\n"
      "対称     : taisyousei / their\n"
      "大賞     : taisyou / theyare\n"
      "才       : sainou / see\n"
      "再       : saikai / c\n"
      "最       : saidai / cee\n";
}

void show_button_information(std::ostream& os) {
  os <<
    "準備OK   : zyunbi / ready\n"
    "最初     : saisyo / first\n"
    "違う     : tigau / no\n"
    "ブランク : buranku / blank\n"
    "なし     : nasi / nothing\n"
    "そう     : sou / yes\n"
    "何？     : nani / what\n"
    "えーと   : eto / e-to / uhhh\n"
    "残り     : nokori / left\n"
    "右       : migi / right\n"
    "真ん中   : maxnnaka / mannnaka / middle\n"
    "オーケー : okey / ok\n"
    "ウェイト : weito / wait\n"
    "押して   : osite / press\n"
    "どう？   : dou? / dou / you\n"
    "導       : mitibiku / youare\n"
    "同       : onaji / your\n"
    "動       : ugoku / youre\n"
    "左       : hidari / ur\n"
    "それ     : sore / u\n"
    "うんうん : uxnun / uxnuxn / uhhuh / unnun / unnunn\n"
    "そうそう : sousou / uhuh\n"
    "え？     : e / e? / whats\n"
    "できた   : dekita / done\n"
    "次       : tugi / next\n"
    "まって   : matte / hold\n"
    "もちろん : motiroxn / motiron / sure\n"
    "例えば   : tatoeba / like\n";
}

}

void ktanehack::WhosOnFirstModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation&)
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
  const std::unordered_map<std::string, ButtonWord> button_map{
    {"ready", ButtonWord::Ready},
    {"zyunbi", ButtonWord::Ready},
    {"準備OK", ButtonWord::Ready},
    {"first", ButtonWord::First},
    {"saisyo", ButtonWord::First},
    {"最初", ButtonWord::First},
    {"no", ButtonWord::No},
    {"tigau", ButtonWord::No},
    {"違う", ButtonWord::No},
    {"blank", ButtonWord::Blank},
    {"buranku", ButtonWord::Blank},
    {"ブランク", ButtonWord::Blank},
    {"nothing", ButtonWord::Nothing},
    {"nasi", ButtonWord::Nothing},
    {"なし", ButtonWord::Nothing},
    {"yes", ButtonWord::Yes},
    {"sou", ButtonWord::Yes},
    {"そう", ButtonWord::Yes},
    {"what", ButtonWord::What},
    {"nani", ButtonWord::What},
    {"何？", ButtonWord::What},
    {"uhhh", ButtonWord::Uhhh},
    {"e-to", ButtonWord::Uhhh},
    {"eto", ButtonWord::Uhhh},
    {"えーと", ButtonWord::Uhhh},
    {"left", ButtonWord::Left},
    {"nokori", ButtonWord::Left},
    {"残り", ButtonWord::Left},
    {"right", ButtonWord::Right},
    {"migi", ButtonWord::Right},
    {"右", ButtonWord::Right},
    {"middle", ButtonWord::Middle},
    {"mannnaka", ButtonWord::Middle},
    {"maxnnaka", ButtonWord::Middle},
    {"真ん中", ButtonWord::Middle},
    {"ok", ButtonWord::Okay},
    {"okey", ButtonWord::Okay},
    {"オーケー", ButtonWord::Okay},
    {"wait", ButtonWord::Wait},
    {"weito", ButtonWord::Wait},
    {"ウェイト", ButtonWord::Wait},
    {"press", ButtonWord::Press},
    {"osite", ButtonWord::Press},
    {"押して", ButtonWord::Press},
    {"you", ButtonWord::You},
    {"dou", ButtonWord::You},
    {"dou?", ButtonWord::You},
    {"どう？", ButtonWord::You},
    {"youare", ButtonWord::YouAre},
    {"mitibiku", ButtonWord::YouAre},
    {"導", ButtonWord::YouAre},
    {"your", ButtonWord::Your},
    {"onaji", ButtonWord::Your},
    {"同", ButtonWord::Your},
    {"youre", ButtonWord::YouRe},
    {"ugoku", ButtonWord::YouRe},
    {"動", ButtonWord::YouRe},
    {"ur", ButtonWord::UR},
    {"hidari", ButtonWord::UR},
    {"左", ButtonWord::UR},
    {"u", ButtonWord::U},
    {"sore", ButtonWord::U},
    {"それ", ButtonWord::U},
    {"uhhuh", ButtonWord::UhHuh},
    {"unnun", ButtonWord::UhHuh},
    {"unnunn", ButtonWord::UhHuh},
    {"uxnuxn", ButtonWord::UhHuh},
    {"uxnun", ButtonWord::UhHuh},
    {"うんうん", ButtonWord::UhHuh},
    {"uhuh", ButtonWord::UhUh},
    {"sousou", ButtonWord::UhUh},
    {"そうそう", ButtonWord::UhUh},
    {"whats", ButtonWord::Whats},
    {"e", ButtonWord::Whats},
    {"e?", ButtonWord::Whats},
    {"え？", ButtonWord::Whats},
    {"done", ButtonWord::Done},
    {"dekita", ButtonWord::Done},
    {"できた", ButtonWord::Done},
    {"next", ButtonWord::Next},
    {"tugi", ButtonWord::Next},
    {"次", ButtonWord::Next},
    {"hold", ButtonWord::Hold},
    {"matte", ButtonWord::Hold},
    {"まって", ButtonWord::Hold},
    {"sure", ButtonWord::Sure},
    {"motiron", ButtonWord::Sure},
    {"motiroxn", ButtonWord::Sure},
    {"もちろん", ButtonWord::Sure},
    {"like", ButtonWord::Like},
    {"tatoeba", ButtonWord::Like},
    {"例えば", ButtonWord::Like},
  };
  const std::unordered_map<ButtonWord, std::vector<ButtonWord>> answer_map{
    {ButtonWord::Ready, {ButtonWord::Yes, ButtonWord::Okay, ButtonWord::Middle, ButtonWord::Left, ButtonWord::Press, ButtonWord::Right, ButtonWord::Blank, ButtonWord::Ready}},
    {ButtonWord::First, {ButtonWord::Left, ButtonWord::Okay, ButtonWord::Yes, ButtonWord::Middle, ButtonWord::No, ButtonWord::Right, ButtonWord::Nothing, ButtonWord::Uhhh, ButtonWord::Wait, ButtonWord::Ready, ButtonWord::Blank, ButtonWord::What, ButtonWord::Press, ButtonWord::First}},
    {ButtonWord::No, {ButtonWord::Blank, ButtonWord::Uhhh, ButtonWord::Wait, ButtonWord::First, ButtonWord::What, ButtonWord::Ready, ButtonWord::Right, ButtonWord::Yes, ButtonWord::Nothing, ButtonWord::Left, ButtonWord::Press, ButtonWord::Okay, ButtonWord::No}},
    {ButtonWord::Blank, {ButtonWord::Wait, ButtonWord::Right, ButtonWord::Okay, ButtonWord::Middle, ButtonWord::Blank}},
    {ButtonWord::Nothing, {ButtonWord::Uhhh, ButtonWord::Right, ButtonWord::Okay, ButtonWord::Middle, ButtonWord::Yes, ButtonWord::Blank, ButtonWord::No, ButtonWord::Press, ButtonWord::Left, ButtonWord::What, ButtonWord::Wait, ButtonWord::First, ButtonWord::Nothing}},
    {ButtonWord::Yes, {ButtonWord::Okay, ButtonWord::Right, ButtonWord::Uhhh, ButtonWord::Middle, ButtonWord::First, ButtonWord::What, ButtonWord::Press, ButtonWord::Ready, ButtonWord::Nothing, ButtonWord::Yes}},
    {ButtonWord::What, {ButtonWord::Uhhh, ButtonWord::What, ButtonWord::Left, ButtonWord::Nothing, ButtonWord::Ready, ButtonWord::Blank, ButtonWord::Middle, ButtonWord::No, ButtonWord::Okay, ButtonWord::First, ButtonWord::Wait}},
    {ButtonWord::Uhhh, {ButtonWord::Ready, ButtonWord::Nothing, ButtonWord::Left, ButtonWord::What, ButtonWord::Okay, ButtonWord::Yes, ButtonWord::Right, ButtonWord::No, ButtonWord::Press, ButtonWord::Blank, ButtonWord::Uhhh}},
    {ButtonWord::Left, {ButtonWord::Right, ButtonWord::Left}},
    {ButtonWord::Right, {ButtonWord::Yes, ButtonWord::Nothing, ButtonWord::Ready, ButtonWord::Press, ButtonWord::No, ButtonWord::Wait, ButtonWord::What, ButtonWord::Right}},
    {ButtonWord::Middle, {ButtonWord::Blank, ButtonWord::Ready, ButtonWord::Okay, ButtonWord::What, ButtonWord::Nothing, ButtonWord::Press, ButtonWord::No, ButtonWord::Wait, ButtonWord::Left, ButtonWord::Middle}},
    {ButtonWord::Okay, {ButtonWord::Middle, ButtonWord::No, ButtonWord::First, ButtonWord::Yes, ButtonWord::Uhhh, ButtonWord::Nothing, ButtonWord::Wait, ButtonWord::Okay}},
    {ButtonWord::Wait, {ButtonWord::Uhhh, ButtonWord::No, ButtonWord::Blank, ButtonWord::Okay, ButtonWord::Yes, ButtonWord::Left, ButtonWord::First, ButtonWord::Press, ButtonWord::What, ButtonWord::Wait}},
    {ButtonWord::Press, {ButtonWord::Right, ButtonWord::Middle, ButtonWord::Yes, ButtonWord::Ready, ButtonWord::Press}},
    {ButtonWord::You, {ButtonWord::Sure, ButtonWord::YouAre, ButtonWord::Your, ButtonWord::YouRe, ButtonWord::Next, ButtonWord::UhHuh, ButtonWord::UR, ButtonWord::Hold, ButtonWord::Whats, ButtonWord::You}},
    {ButtonWord::YouAre, {ButtonWord::Your, ButtonWord::Next, ButtonWord::Like, ButtonWord::UhHuh, ButtonWord::Whats, ButtonWord::Done, ButtonWord::UhUh, ButtonWord::Hold, ButtonWord::You, ButtonWord::U, ButtonWord::YouRe, ButtonWord::Sure, ButtonWord::UR, ButtonWord::YouAre}},
    {ButtonWord::Your, {ButtonWord::UhUh, ButtonWord::YouAre, ButtonWord::UhHuh, ButtonWord::Your}},
    {ButtonWord::YouRe, {ButtonWord::You, ButtonWord::YouRe}},
    {ButtonWord::UR, {ButtonWord::Done, ButtonWord::U, ButtonWord::UR}},
    {ButtonWord::U, {ButtonWord::UhHuh, ButtonWord::Sure, ButtonWord::Next, ButtonWord::Whats, ButtonWord::YouRe, ButtonWord::UR, ButtonWord::UhUh, ButtonWord::Done, ButtonWord::U}},
    {ButtonWord::UhHuh, {ButtonWord::UhHuh}},
    {ButtonWord::UhUh, {ButtonWord::UR, ButtonWord::U, ButtonWord::YouAre, ButtonWord::YouRe, ButtonWord::Next, ButtonWord::UhUh}},
    {ButtonWord::Whats, {ButtonWord::You, ButtonWord::Hold, ButtonWord::YouRe, ButtonWord::Your, ButtonWord::U, ButtonWord::Done, ButtonWord::UhUh, ButtonWord::Like, ButtonWord::YouAre, ButtonWord::UhHuh, ButtonWord::UR, ButtonWord::Next, ButtonWord::Whats}},
    {ButtonWord::Done, {ButtonWord::Sure, ButtonWord::UhHuh, ButtonWord::Next, ButtonWord::Whats, ButtonWord::Your, ButtonWord::UR, ButtonWord::YouRe, ButtonWord::Hold, ButtonWord::Like, ButtonWord::You, ButtonWord::U, ButtonWord::YouAre, ButtonWord::UhUh, ButtonWord::Done}},
    {ButtonWord::Next, {ButtonWord::Whats, ButtonWord::UhHuh, ButtonWord::UhUh, ButtonWord::Your, ButtonWord::Hold, ButtonWord::Sure, ButtonWord::Next}},
    {ButtonWord::Hold, {ButtonWord::YouAre, ButtonWord::U, ButtonWord::Done, ButtonWord::UhUh, ButtonWord::You, ButtonWord::UR, ButtonWord::Sure, ButtonWord::Whats, ButtonWord::YouRe, ButtonWord::Next, ButtonWord::Hold}},
    {ButtonWord::Sure, {ButtonWord::YouAre, ButtonWord::Done, ButtonWord::Like, ButtonWord::YouRe, ButtonWord::You, ButtonWord::Hold, ButtonWord::UhHuh, ButtonWord::UR, ButtonWord::Sure}},
    {ButtonWord::Like, {ButtonWord::YouRe, ButtonWord::Next, ButtonWord::U, ButtonWord::UR, ButtonWord::Hold, ButtonWord::Done, ButtonWord::UhUh, ButtonWord::Whats, ButtonWord::UhHuh, ButtonWord::You, ButtonWord::Like}}
  };

  while (true) {
    os << "What display?\n";
    show_display_information(os);
    if (const auto it{display_map.find(get_value<std::string>(is))}; it == display_map.end())
      break;
    else
      os << to_string(place_map.at(it->second)) << " : Whats words?\n";
    show_button_information(os);

    if (const auto it{button_map.find(get_value<std::string>(is))}; it == button_map.end())
      continue;
    else {
      os << "---ANSWERS under---\n";
      for (const auto& e : answer_map.at(it->second))
        os << to_string(e) << '\n';
      os << "---ANSWERS above---\n";
    }
  }
}
