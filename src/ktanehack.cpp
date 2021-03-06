#include "ktanehack.hpp"

#include <functional>
#include <string>
#include <unordered_map>

#include <xmaho/input/input.hpp>

#include "module/wire.hpp"
#include "module/button.hpp"
#include "module/keypads.hpp"
#include "module/simon.hpp"
#include "module/whos_on_first.hpp"
#include "module/memory.hpp"
#include "module/morse_code.hpp"

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
    {"s", &std::make_unique<SimonModule>},
    {"simon", &std::make_unique<SimonModule>},
    {"wh", &std::make_unique<WhosOnFirstModule>},
    {"whos", &std::make_unique<WhosOnFirstModule>},
    {"m", &std::make_unique<MemoryModule>},
    {"memory", &std::make_unique<MemoryModule>},
    {"mo", &std::make_unique<MorseCodeModule>},
    {"c", &std::make_unique<MorseCodeModule>},
    {"morse", &std::make_unique<MorseCodeModule>},
    {"code", &std::make_unique<MorseCodeModule>},
  };

  os << "Modules:\n"
        "  Wires (horizon): w/wires/hw\n"
        "  Button         : b/button\n"
        "  Keypads        : k/keypads\n"
        "  Simon Says     : s/simon\n"
        "  Whos on First  : wh/whos\n"
        "  Memory         : m/memory\n"
        "  Morse Code     : mo/c/morse/code\n";

  auto it{module_map.find(xmaho::input::get_value<std::string>(is))};
  return it != module_map.end() ? it->second() : nullptr;
}
