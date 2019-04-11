#include "ktanehack.hpp"

#include <functional>
#include <string>
#include <unordered_map>

#include <xmaho/input/input.hpp>

namespace ktanehack
{

std::unique_ptr<Module> get_module(std::istream& is)
{
  static const std::unordered_map<std::string, std::function<std::unique_ptr<Module>(std::istream&)>> module_map{
    {"wire", [](std::istream&){return nullptr;}}
  };

  auto it{module_map.find(xmaho::input::get_value<std::string>(is))};
  return it != module_map.end() ? it->second(is) : nullptr;
}

}
