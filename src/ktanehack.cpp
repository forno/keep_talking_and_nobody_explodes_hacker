#include "ktanehack.hpp"

#include <functional>
#include <string>
#include <unordered_map>

#include <xmaho/input/input.hpp>

#include "module/wire.hpp"

namespace
{

template<typename T>
inline void show_construct_message(std::ostream& os)
{
  T::show_construct_message(os);
}

template<typename T>
inline std::unique_ptr<ktanehack::Module> make_module(std::istream& is, std::ostream& os)
{
  show_construct_message<T>(os);
  return std::make_unique<T>(is); 
}

}

void ktanehack::show_modules(std::ostream& os)
{
  os << "Modules:\n"
        "  wire: horizon wire (type: w/wire/hw)\n";
}

std::unique_ptr<ktanehack::Module> ktanehack::get_module(std::istream& is, std::ostream& os)
{
  static const std::unordered_map<std::string, std::function<std::unique_ptr<Module>(std::istream&, std::ostream& os)>> module_map{
    {"hw", &make_module<WireModule>},
    {"w", &make_module<WireModule>},
    {"wire", &make_module<WireModule>},
  };

  auto it{module_map.find(xmaho::input::get_value<std::string>(is))};
  return it != module_map.end() ? it->second(is, os) : nullptr;
}
