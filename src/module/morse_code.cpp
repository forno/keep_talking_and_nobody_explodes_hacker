#include "module/morse_code.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <unordered_map>
#include <valarray>

#include <xmaho/input/input.hpp>

namespace
{

template<typename T>
class IncrementGuard
{
public:
  IncrementGuard(T& v)
    : v_{v}
  {
  }

  ~IncrementGuard()
  {
    ++v_;
  }

private:
  T& v_;
};

}

void ktanehack::MorseCodeModule::defuse(std::istream& is, std::ostream& os, ktanehack::BombInformation&)
{
  using xmaho::input::get_value;

  const std::unordered_map<std::string, char> interpret_map{
    {".-",   'a'},
    {"-...", 'b'},
    {"-.-.", 'c'},
    {"-..",  'd'},
    {".",    'e'},
    {"..-.", 'f'},
    {"--.",  'g'},
    {"....", 'h'},
    {"..",   'i'},
    {".---", 'j'},
    {"-.-",  'k'},
    {".-..", 'l'},
    {"--",   'm'},
    {"-.",   'n'},
    {"---",  'o'},
    {".--.", 'p'},
    {"--.-", 'q'},
    {"--.-", 'r'},
    {"...",  's'},
    {"-",    't'},
    {"..-",  'u'},
    {"...-", 'v'},
    {".--",  'w'},
    {"-..-", 'x'},
    {"-.--", 'y'},
    {"--..", 'z'}
  };
  const std::unordered_map<std::string, int> answer_map{
    {"shell", 505},
    {"halls", 515},
    {"slick", 522},
    {"trick", 532},
    {"boxes", 535},
    {"leaks", 542},
    {"strobe", 545},
    {"bistro", 552},
    {"flick", 555},
    {"bombs", 565},
    {"break", 572},
    {"brick", 575},
    {"steak", 582},
    {"sting", 592},
    {"vector", 595},
    {"beats", 600}
  };

  std::string base_input{};
  while (true) {
    os << "Please input Morse Code with . or -\n";
    const auto it{interpret_map.find(get_value<std::string>(is))};
    if (it == interpret_map.end())
      break;
    base_input.push_back(it->second);
    std::valarray<bool> found_flags(answer_map.size());
    for (auto i{base_input.size()}; i; --i) {
      std::rotate(base_input.begin(), std::next(base_input.begin()), base_input.end());
      {
        auto index {0u};
        for (const auto& e : answer_map) {
          IncrementGuard{index};
          if (e.first.find(base_input) != std::string::npos)
            found_flags[index] = true;
        }
      }
      const std::string_view input_word{base_input};
      for (auto j{1u}; j < base_input.size(); ++j) {
        const auto last_words{base_input.substr(j)};
        const auto forward_words{base_input.substr(0, j)};
        auto index{0u};
        for (const auto& e : answer_map) {
          IncrementGuard{index};
          if (e.first.find(last_words) != (e.first.size() - last_words.size()))
            continue;
          if (e.first.find(forward_words) != 0)
            continue;
          found_flags[index] = true;
        }
      }
    }
    auto index{0u};
    for (const auto& e : answer_map) {
      IncrementGuard{index};
      if (found_flags[index])
        os << e.first << " : " << e.second << '\n';
    }
  }
}
