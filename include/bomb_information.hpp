#ifndef KTANEHACK_BOMB_INFORMATION_HPP
#define KTANEHACK_BOMB_INFORMATION_HPP

#include <iosfwd>
#include <optional>
#include <string>
#include <unordered_map>

namespace ktanehack
{

class BombInformation
{
public:
  BombInformation(std::istream& is, std::ostream& os);

  bool known_battery_count();
  bool known_serial_containing_vowel();
  bool known_serial_last_value_odd();

  bool is_serial_containing_vowel();
  bool is_serial_last_value_odd();
  int battery_count();

  bool has_indicator(std::string indicator);

private:
  std::istream& is_;
  std::ostream& os_;
  std::optional<bool> is_serial_containing_vowel_;
  std::optional<bool> is_serial_last_value_odd_;
  std::optional<int> battery_count_;
  std::unordered_map<std::string, bool> indicators_;
};

}

#endif
