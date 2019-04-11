#ifndef KTANEHACK_KTANEHACK_HPP
#define KTANEHACK_KTANEHACK_HPP

#include <iosfwd>
#include <memory>
#include <optional>

#include "module.hpp"

namespace ktanehack
{

void show_modules(std::ostream& os);

std::unique_ptr<Module> get_module(std::istream& is);

}

#endif
