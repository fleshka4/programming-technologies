#include <iostream>
#include <stdexcept>
#include <vector>
#include "tasks.hpp"
#include "utilities.hpp"

void doThirdTask()
{
  std::vector<int> vector;
  int number = 0;
  while (std::cin >> number) {
    if (number == 0) {
      break;
    }
    vector.push_back(number);
  }

  if (std::cin.fail() && !std::cin.eof()) {
    throw std::invalid_argument("Error with reading integer numbers!");
  }
  if (vector.empty()) {
    return;
  }
  if (number != 0) {
    throw std::runtime_error("Last value must be 0!");
  }

  if (vector.back() == 1) {
    for (auto i = vector.begin(); i != vector.end();) {
      if ((*i % 2) == 0) {
        i = vector.erase(i);
      } else {
        ++i;
      }
    }
  } else if (vector.back() == 2) {
    for (auto i = vector.begin(); i != vector.end();) {
      if ((*i % 3 == 0)) {
        i = vector.insert(++i, 3, 1) + 3;
      } else {
        ++i;
      }
    }
  }

  print(vector);
  std::cout << '\n';
}
