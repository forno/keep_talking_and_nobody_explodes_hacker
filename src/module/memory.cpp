#include "module/memory.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <xmaho/input/input.hpp>


void ktanehack::MemoryModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation&)
{
  using xmaho::input::get_value;

  std::vector<std::pair<int, int>> memories{};

  const auto store_place{[&](auto number){return [&, number]{os << "Press labeled " << number << "\nWhere position?\n"; return std::make_pair(get_value<int>(is), number);};}};
  const auto store_number{[&](auto place){return [&, place]{os << "Press " << place << " position\nWhats value?\n"; return std::make_pair(place, get_value<int>(is));};}};
  const auto store_place_with_memory{[&](auto stage){return [&, stage]{return store_place(memories.at(stage - 1).second)();};}};
  const auto store_number_with_memory{[&](auto stage){return [&, stage]{return store_number(memories.at(stage - 1).first)();};}};
  const auto show_label{[&](auto stage){return [&, stage]{os << "Press labeled " << memories.at(stage - 1).second << '\n'; return std::pair<int, int>{};};}};
  const std::array<std::array<std::function<std::pair<int, int>()>, 4>, 5> jobs_map{{
    {store_number(2), store_number(2), store_number(3), store_number(4)},
    {store_place(4), store_number_with_memory(1), store_number(1), store_number_with_memory(1)},
    {store_place_with_memory(2), store_place_with_memory(1), store_number(3), store_place(4)},
    {store_number_with_memory(1), store_number(1), store_number_with_memory(2), store_number_with_memory(2)},
    {show_label(1), show_label(2), show_label(4), show_label(3)}
  }};

  for (const auto& job : jobs_map) {
    os << "What number on display?\n";
    try {
      memories.push_back(job.at(get_value<std::size_t>(is) - 1)());
    } catch (const std::out_of_range& e) {
      os << e.what() << '\n';
      return;
    }
  }
}
