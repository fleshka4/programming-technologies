#include <forward_list>
#include <functional>
#include <vector>
#include "tasks.hpp"
#include "utilities.hpp"

void input(std::vector<int>& vector);

void doFirstTask(const std::function<bool(int, int)>& compare)
{
  std::vector<int> vector;
  input(vector);

  std::vector<int> vectorAt(vector);
  std::forward_list<int> forwardList(vector.begin(), vector.end());

  sort<OperatorAccess>(vector, compare);
  print(vector);
  std::cout << '\n';

  sort<AtAccess>(vectorAt, compare);
  print(vectorAt);
  std::cout << '\n';

  sort<IteratorAccess>(forwardList, compare);
  print(forwardList);
  std::cout << '\n';
}

void input(std::vector<int>& vector)
{
  int num;
  while (std::cin >> num) {
    vector.push_back(num);
  }
  if (!std::cin.eof()) {
    throw std::invalid_argument("Error with reading integer numbers!");
  }
}
