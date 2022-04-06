#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <stdexcept>

#include "accessor.hpp"

template<typename T>
std::function<bool(const T&, const T&)> getComparator(const char* order)
{
  if (order == nullptr) {
    throw std::invalid_argument("Invalid sorting order!");
  }
  if (std::strcmp("ascending", order) == 0) {
    return std::greater<T>();
  }
  if (std::strcmp("descending", order) == 0) {
    return std::less<T>();
  }
  throw std::invalid_argument("Invalid sorting order!");
}

template<template<typename> class Accessor, typename Container>
void sort(Container& container, const std::function<bool(typename Container::value_type,
    typename Container::value_type)>& compare) {
  using AccessType = Accessor<Container>;

  const auto begin = AccessType::begin(container);
  const auto end = AccessType::end(container);

  for (auto i = begin; i != end; ++i) {
    for (auto j = i; j != end; ++j) {
      if (compare(AccessType ::get(container, i), AccessType::get(container, j))) {
        std::swap(AccessType::get(container, i), AccessType::get(container, j));
      }
    }
  }
}

template<typename Container>
void print(const Container& container, const char* separator = " ") {
  if (separator == nullptr) {
    throw std::invalid_argument("Separator must not be a nullptr!");
  }
  for (auto i = container.begin(); i != container.end(); ++i) {
    std::cout << *i << separator;
  }
}

#endif
