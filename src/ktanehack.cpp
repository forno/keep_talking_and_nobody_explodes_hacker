#include "ktanehack.hpp"

#include <functional>
#include <string>
#include <unordered_map>

#include <xmaho/input/input.hpp>

#include "module/wire.hpp"
#include "module/button.hpp"
#include "module/keypads.hpp"
#include "module/simon.hpp"

std::unique_ptr<ktanehack::Module> ktanehack::get_module(std::istream& is, std::ostream& os)
{
  const std::unordered_map<std::string, std::function<std::unique_ptr<Module>()>> module_map{
    {"hw", &std::make_unique<WireModule>},
    {"w", &std::make_unique<WireModule>},
    {"wires", &std::make_unique<WireModule>},
    {"b", &std::make_unique<ButtonModule>},
    {"button", &std::make_unique<ButtonModule>},
    {"k", &std::make_unique<KeypadsModule>},
    {"keypads", &std::make_unique<KeypadsModule>},
    {"k", &std::make_unique<SimonModule>},
    {"keypads", &std::make_unique<SimonModule>},
  };

  os << "Modules:\n"
        "  Wires (horizon): w/wires/hw\n"
        "  Button         : b/button\n"
        "  Keypads        : k/keypads\n"
        "  Simon Says     : s/simon\n";

  auto it{module_map.find(xmaho::input::get_value<std::string>(is))};
  return it != module_map.end() ? it->second() : nullptr;
}
