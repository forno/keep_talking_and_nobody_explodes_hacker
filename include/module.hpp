#ifndef KTANEHACK_MODULE_HPP
#define KTANEHACK_MODULE_HPP

#include <iosfwd>

namespace ktanehack
{

class Module
{
public:
  Module() = delete;
  virtual ~Module() = default;

  virtual void defuse(std::istream& is) = 0;
};

}

#endif
