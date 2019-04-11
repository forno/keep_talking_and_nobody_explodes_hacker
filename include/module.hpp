#ifndef KTANEHACK_MODULE_HPP
#define KTANEHACK_MODULE_HPP

#include <iosfwd>

namespace ktanehack
{

class Module
{
public:
  virtual ~Module() = default;

  virtual void defuse(std::istream& is, std::ostream& os) = 0;
};

}

#endif
