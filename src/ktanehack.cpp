#include "ktanehack.hpp"

#include <functional>
#include <string>
#include <unordered_map>

#include <xmaho/input/input.hpp>

#include "module/wire.hpp"

std::unique_ptr<ktanehack::Module> ktanehack::get_module(std::istream& is, std::ostream& os)
{
  static const std::unordered_map<std::string, std::function<std::unique_ptr<Module>()>> module_map{
    {"hw", &std::make_unique<WireModule>},
    {"w", &std::make_unique<WireModule>},
    {"wires", &std::make_unique<WireModule>},
  };

  os << "Modules:\n"
        "  wire: horizon wire (type: w/wires/hw)\n";

  auto it{module_map.find(xmaho::input::get_value<std::string>(is))};
  return it != module_map.end() ? it->second() : nullptr;
}
