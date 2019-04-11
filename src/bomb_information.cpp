#include "bomb_information.hpp"

#include <optional>
#include <utility>

#include <xmaho/input/input.hpp>

ktanehack::BombInformation::BombInformation(std::istream& is, std::ostream& os)
  : is_{is},
    os_{os}
{
}

bool ktanehack::BombInformation::known_serial_containing_vowel()
{
  return is_serial_containing_vowel_.has_value();
}

bool ktanehack::BombInformation::known_serial_last_value_odd()
{
  return is_serial_last_value_odd_.has_value();
}

bool ktanehack::BombInformation::known_battery_count()
{
  return battery_count_.has_value();
}

bool ktanehack::BombInformation::is_serial_containing_vowel()
{
  if (is_serial_containing_vowel_)
    return is_serial_containing_vowel_.value();
  do {
    is_.clear();
    os_ << "Do SERIAL contains VOEWL? [true(1)/false(0)]\n";
    is_serial_containing_vowel_ = xmaho::input::get_value<bool>(is_);
  } while (!is_serial_containing_vowel_);
  return is_serial_containing_vowel_.value();
}

bool ktanehack::BombInformation::is_serial_last_value_odd()
{
  if (is_serial_last_value_odd_)
    return is_serial_last_value_odd_.value();
  do {
    is_.clear();
    os_ << "Is SERIAL's LAST value ODD? [true(1)/false(0)]\n";
    is_serial_last_value_odd_ = xmaho::input::get_value<bool>(is_);
  } while (!is_serial_last_value_odd_);
  return is_serial_last_value_odd_.value();
}

int ktanehack::BombInformation::battery_count()
{
  if (battery_count_)
    return battery_count_.value();
  do {
    is_.clear();
    os_ << "Please count batteries\n";
    battery_count_ = xmaho::input::get_value<int>(is_);
  } while (!battery_count_);
  return battery_count_.value();
}

bool ktanehack::BombInformation::has_indicator(std::string indicator)
{
  const auto it{indicators_.find(indicator)};
  if (it != indicators_.end())
    return it->second;
  is_.clear();
  os_ << "Does the bomb have " << indicator << " indicator? [true(1)/false(0)]";
  const auto exist{xmaho::input::get_value<bool>(is_)};
  indicators_.emplace(std::move(indicator), exist);
  return exist;
}
