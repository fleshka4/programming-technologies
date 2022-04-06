#ifndef FACTORIAL_CONTAINER_HPP
#define FACTORIAL_CONTAINER_HPP

#include <iterator>

size_t getFactorial(size_t n);

class FactorialContainer {
public:
  class iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, std::ptrdiff_t, size_t, size_t> {
  public:
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);

    value_type operator*() const;

    bool operator==(const iterator& iter) const;
    bool operator!=(const iterator& iter) const;

  private:
    friend FactorialContainer;

    iterator(value_type value, value_type position, value_type maxPos);

    size_t value_;
    size_t position_;
    const size_t maxPos_;
  };

  using const_iterator = iterator;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  FactorialContainer();
  explicit FactorialContainer(size_t size);

  const_iterator begin() const noexcept;
  const_reverse_iterator rbegin() const noexcept;

  const_iterator end() const noexcept;
  const_reverse_iterator rend() const noexcept;

private:
  const size_t size_;
  const size_t maxFactorial_;
};

#endif
