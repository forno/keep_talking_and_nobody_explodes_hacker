#ifndef KTANEHACK_KTANEHACK_HPP
#define KTANEHACK_KTANEHACK_HPP

#include <iosfwd>
#include <memory>
#include <optional>

#include "module.hpp"

namespace ktanehack
{

std::unique_ptr<Module> get_module(std::istream& is, std::ostream& os);

}

#endif
