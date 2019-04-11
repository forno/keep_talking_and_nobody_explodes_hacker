#include "module/keypads.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <xmaho/input/input.hpp>

namespace
{

enum class Symbol
{
  AWithVirtical,
  Ash,
  Asterisk,
  BWithT,
  CMirrorWithDot,
  CWithDot,
  CopyRight,
  EMirrorWithUmlaut,
  ExclamationInverse,
  HWithAddition,
  Invader,
  KiKatakanaJapanese,
  Lambda,
  NMirror,
  NWithAngelHoop,
  NicoMark,
  OWithVirtical,
  Omega,
  OmegaWithApostrophe,
  Psi,
  QOneStroke,
  QWithFill,
  Six,
  StarFill,
  StarLine,
  ThreeAddition,
  ThreeInvalid,
};

std::string to_string(Symbol s)
{
  switch (s) {
    case Symbol::AWithVirtical:
      return "A";
    case Symbol::Ash:
      return "ae";
    case Symbol::Asterisk:
      return "*";
      case Symbol::BWithT:
        return "b";
    case Symbol::CMirrorWithDot:
      return "C mirror: cm";
    case Symbol::CWithDot:
      return "C";
    case Symbol::CopyRight:
      return "©";
    case Symbol::EMirrorWithUmlaut:
      return "E mirror with umlaut : carl";
    case Symbol::ExclamationInverse:
      return "? : exclamation";
    case Symbol::HWithAddition:
      return "H / x";
    case Symbol::Invader:
      return "invader / shield / enemy";
    case Symbol::KiKatakanaJapanese:  return "キ : ki";
    case Symbol::Lambda:
      return "λ : lambda";
    case Symbol::NMirror:
      return "N";
    case Symbol::NWithAngelHoop:
      return "N with angel hoop : n_hoop_";
    case Symbol::NicoMark:
      return "nico";
    case Symbol::OWithVirtical:
      return "O : balloon";
    case Symbol::Omega:
      return "Ω : omega";
    case Symbol::OmegaWithApostrophe:
      return "ω : omega with apostrophe";
    case Symbol::Psi:
      return "ψ : psi";
    case Symbol::QOneStroke:
      return "Q";
    case Symbol::QWithFill:
      return "q";
    case Symbol::Six:
      return "6";
    case Symbol::StarFill:
      return "★ : sb";
    case Symbol::StarLine:
      return "☆ : sw";
    case Symbol::ThreeAddition:
      return "3_add (like a worm)";
    case Symbol::ThreeInvalid:
      return "3 (mistake)";
  }

  throw std::invalid_argument{"ktanehack::KeyupadsModule::(anonymous)::to_string(ktanehack::KeyupadsModule::(anonymous)::Symbol): Undefined string"};
}

}

void ktanehack::KeypadsModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation&)
{
  using xmaho::input::get_value;

  static const std::unordered_map<std::string, Symbol> symbol_map{
    {"A", Symbol::AWithVirtical},
    {"a", Symbol::AWithVirtical},
    {"ae", Symbol::Ash},
    {"ash", Symbol::Ash},
    {"æ̀", Symbol::Ash},
    {"ǽ", Symbol::Ash},
    {"*", Symbol::Asterisk},
    {"asterisk", Symbol::Asterisk},
    {"B", Symbol::BWithT},
    {"b", Symbol::BWithT},
    {"bt", Symbol::BWithT},
    {"Cm", Symbol::CMirrorWithDot}, // C Mirror
    {"Ci", Symbol::CMirrorWithDot}, // C Inverse
    {"cm", Symbol::CMirrorWithDot}, // C Mirror
    {"ci", Symbol::CMirrorWithDot}, // C Inverse
    {"C", Symbol::CWithDot},
    {"c", Symbol::CWithDot},
    {"copy", Symbol::CopyRight},
    {"©", Symbol::CopyRight},
    {"carl", Symbol::EMirrorWithUmlaut},
    {"E", Symbol::EMirrorWithUmlaut},
    {"e", Symbol::EMirrorWithUmlaut},
    {"?", Symbol::ExclamationInverse},
    {"exclamation", Symbol::ExclamationInverse},
    {"H", Symbol::HWithAddition},
    {"h", Symbol::HWithAddition},
    {"X", Symbol::HWithAddition},
    {"x", Symbol::HWithAddition},
    {"enemy", Symbol::Invader},
    {"invadar", Symbol::Invader},
    {"shield", Symbol::Invader},
    {"ki", Symbol::KiKatakanaJapanese},
    {"キ", Symbol::KiKatakanaJapanese},
    {"lambda", Symbol::Lambda},
    {"λ", Symbol::Lambda},
    {"N", Symbol::NMirror},
    {"n", Symbol::NMirror},
    {"N_angel", Symbol::NWithAngelHoop},
    {"N_cap", Symbol::NWithAngelHoop},
    {"N_hoop", Symbol::NWithAngelHoop},
    {"n_angel", Symbol::NWithAngelHoop},
    {"n_cap", Symbol::NWithAngelHoop},
    {"n_hoop", Symbol::NWithAngelHoop},
    {"mark", Symbol::NicoMark},
    {"nico", Symbol::NicoMark},
    {"balloon", Symbol::OWithVirtical},
    {"O", Symbol::OWithVirtical},
    {"o", Symbol::OWithVirtical},
    {"hip", Symbol::OmegaWithApostrophe},
    {"oshiri", Symbol::OmegaWithApostrophe},
    {"osiri", Symbol::OmegaWithApostrophe},
    {"ω", Symbol::OmegaWithApostrophe},
    {"omega", Symbol::Omega},
    {"Ω", Symbol::Omega},
    {"psi", Symbol::Psi},
    {"ψ", Symbol::Psi},
    {"Ψ", Symbol::Psi},
    {"psi", Symbol::Psi},
    {"Q", Symbol::QWithFill},
    {"q", Symbol::QWithFill},
    {"6", Symbol::Six},
    {"siguma", Symbol::Six},
    {"six", Symbol::Six},
    {"σ", Symbol::Six},
    {"sb", Symbol::StarFill},
    {"sf", Symbol::StarFill},
    {"star_black", Symbol::StarFill},
    {"star_fill", Symbol::StarFill},
    {"sl", Symbol::StarLine},
    {"star_line", Symbol::StarLine},
    {"star_white", Symbol::StarLine},
    {"sw", Symbol::StarLine},
    {"3_add", Symbol::ThreeAddition},
    {"catarpillar", Symbol::ThreeAddition},
    {"three_add", Symbol::ThreeAddition},
    {"worm", Symbol::ThreeAddition},
    {"3", Symbol::ThreeInvalid},
    {"three", Symbol::ThreeInvalid},
  };
  static const std::vector<std::vector<Symbol>> symbol_lines{
    {Symbol::OWithVirtical, Symbol::AWithVirtical, Symbol::Lambda, Symbol::NMirror, Symbol::Invader, Symbol::HWithAddition, Symbol::CMirrorWithDot},
    {Symbol::EMirrorWithUmlaut, Symbol::OWithVirtical, Symbol::CMirrorWithDot, Symbol::QOneStroke, Symbol::StarLine, Symbol::HWithAddition, Symbol::ExclamationInverse},
    {Symbol::CopyRight, Symbol::OmegaWithApostrophe, Symbol::QOneStroke, Symbol::Asterisk, Symbol::ThreeInvalid, Symbol::Lambda, Symbol::StarLine},
    {Symbol::Six, Symbol::QWithFill, Symbol::BWithT, Symbol::Invader, Symbol::Asterisk, Symbol::ExclamationInverse, Symbol::NicoMark},
    {Symbol::Psi, Symbol::NicoMark, Symbol::BWithT, Symbol::CWithDot, Symbol::QWithFill, Symbol::ThreeAddition, Symbol::StarFill},
    {Symbol::Six, Symbol::EMirrorWithUmlaut, Symbol::KiKatakanaJapanese, Symbol::Ash, Symbol::Psi, Symbol::NWithAngelHoop, Symbol::Omega}
  };

  std::vector<Symbol> displayed{};
  while (displayed.size() < 4) {
    os << "----Symbol list----\n"
          "A\n"
          "ae\n"
          "*\n"
          "b\n"
          "C mirror: cm\n"
          "C\n"
          "©\n"
          "E mirror with umlaut : carl\n"
          "? : exclamation\n"
          "H / x\n"
          "invader / shield / enemy\n"
          "キ : ki\n"
          "λ : lambda\n"
          "N\n"
          "N with angel hoop : n_hoop_\n"
          "nico\n"
          "O : balloon\n"
          "Ω : omega\n"
          "ω : omega with apostrophe\n"
          "ψ : psi\n"
          "Q\n"
          "q\n"
          "6\n"
          "★ : sb\n"
          "☆ : sw\n"
          "3_add (like a worm)\n"
          "3 (mistake)\n";
    const auto it{symbol_map.find(xmaho::input::get_value<std::string>(is))};
    if (it == symbol_map.end())
      continue;
    displayed.push_back(it->second);
  }

  for (const auto& symbol_line : symbol_lines) {
    std::vector<std::size_t> index_map{};
    auto is_not_found{false};
    for (auto i {0u}; i < displayed.size(); ++i) {
      const auto it{std::find(symbol_line.begin(), symbol_line.end(), displayed[i])};
      if (it == symbol_line.end()) {
        is_not_found = true;
        break;
      }
      index_map.push_back(it - symbol_line.begin());
    }

    if (is_not_found)
      continue;
    os << "---- show order ----\n";
    for (auto i {displayed.size()}; i; --i) {
      const auto it {std::min_element(index_map.begin(), index_map.end())};
      os << to_string(displayed[it - index_map.begin()]) << '\n';
      *it = std::numeric_limits<decltype(index_map)::value_type>::max();
    }
    return;
  }

  os << "Error: Symbol list not found\n";
  return;
}
