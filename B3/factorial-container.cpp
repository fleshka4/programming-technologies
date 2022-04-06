#include "factorial-container.hpp"

#include <limits>
#include <stdexcept>

size_t getFactorial(size_t n)
{
  if (n > 1) {
    size_t result = 1;
    for (size_t i = 2; i < n + 1; ++i) {
      if (result > (std::numeric_limits<size_t>::max() / i)) {
        throw std::overflow_error("The factorial value exceeded the maximum value!");
      }
      result *= i;
    }
    return result;
  }
  return 1;
}

FactorialContainer::iterator::iterator(value_type value, value_type position, value_type maxPos):
  value_(value),
  position_(position),
  maxPos_(maxPos)
{}

FactorialContainer::iterator& FactorialContainer::iterator::operator++()
{
  if (position_ >= maxPos_) {
    throw std::out_of_range("You are out of bounds!");
  }
  ++position_;
  value_ *= position_;
  return *this;
}

FactorialContainer::iterator FactorialContainer::iterator::operator++(int)
{
  FactorialContainer::iterator temp(*this);
  ++(*this);
  return temp;
}

FactorialContainer::iterator& FactorialContainer::iterator::operator--()
{
  if (position_ == 1) {
    throw std::out_of_range("You are out of bounds!");
  }
  value_ /= position_;
  --position_;
  return *this;
}

FactorialContainer::iterator FactorialContainer::iterator::operator--(int)
{
  FactorialContainer::iterator temp(*this);
  --(*this);
  return temp;
}

FactorialContainer::iterator::value_type FactorialContainer::iterator::operator*() const
{
  return value_;
}

bool FactorialContainer::iterator::operator==(const FactorialContainer::iterator& iter) const
{
  return (position_ == iter.position_);
}

bool FactorialContainer::iterator::operator!=(const FactorialContainer::iterator& iter) const
{
  return !(iter == *this);
}

FactorialContainer::FactorialContainer():
  size_(0),
  maxFactorial_(getFactorial(size_))
{}

FactorialContainer::FactorialContainer(size_t size):
  size_(size + 1),
  maxFactorial_(getFactorial(size_))
{}

FactorialContainer::const_iterator FactorialContainer::begin() const noexcept
{
  return {1, 1, size_};
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const noexcept
{
  return FactorialContainer::const_reverse_iterator(end());
}

FactorialContainer::const_iterator FactorialContainer::end() const noexcept
{
  return {maxFactorial_, (size_ == 0) ? 1 : size_, size_};
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const noexcept
{
  return FactorialContainer::const_reverse_iterator(begin());
}
