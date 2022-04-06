#include "utility.hpp"

#include <cctype>
#include <istream>

std::istream& skipWS(std::istream& in)
{
  while (std::isblank(in.peek())) {
    in.get();
  }
  return in;
}
