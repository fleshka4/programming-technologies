#ifndef ACCESSOR_HPP
#define ACCESSOR_HPP

#include <stdexcept>

template<typename Container>
struct OperatorAccess {
  using Iterator = typename Container::size_type;
  using Value = typename Container::value_type;

  static Iterator begin(const Container&)
  {
    return 0;
  }

  static Iterator end(const Container& container)
  {
    return container.size();
  }

  static Value& get(Container& container, Iterator index)
  {
    if (index >= container.size()) {
      throw std::out_of_range("Wrong index!");
    }
    return container[index];
  }
};

template<typename Container>
struct AtAccess {
  using Iterator = typename Container::size_type;
  using Value = typename Container::value_type;

  static Iterator begin(const Container&)
  {
    return 0;
  }

  static Iterator end(const Container& container)
  {
    return container.size();
  }

  static Value& get(Container& container, Iterator index)
  {
    return container.at(index);
  }
};

template<typename Container>
struct IteratorAccess {
  using Iterator = typename Container::iterator;
  using Value = typename Container::value_type;

  static Iterator begin(Container& container)
  {
    return container.begin();
  }

  static Iterator end(Container& container)
  {
    return container.end();
  }

  static Value& get(Container&, Iterator index)
  {
    return *index;
  }
};

#endif
