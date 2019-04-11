#ifndef KTANEHACK_BOMB_INFORMATION_HPP
#define KTANEHACK_BOMB_INFORMATION_HPP

#include <iosfwd>
#include <optional>

namespace ktanehack
{

class BombInformation
{
public:
  BombInformation(std::istream& is, std::ostream& os);
  bool is_serial_containing_vowel();
  bool is_serial_last_value_odd();
  int battery_count();

private:
  std::istream& is_;
  std::ostream& os_;
  std::optional<bool> is_serial_containing_vowel_;
  std::optional<bool> is_serial_last_value_odd_;
  std::optional<int> battery_count_;
};

}

#endif
