#include <functional>
#include <random>
#include <vector>
#include "tasks.hpp"
#include "utilities.hpp"

void fillRandom(double* array, int size)
{
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_real_distribution<> dis(-1.0, 1.0);

  for (int i = 0; i < size; ++i) {
    array[i] = dis(gen);
  }
}

void doFourthTask(const std::function<bool(double, double)>& compare, int size)
{
  if (size <= 0 ) {
    throw std::invalid_argument("Size must be positive!");
  }

  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector);
  std::cout << '\n';

  sort<OperatorAccess>(vector, compare);
  print(vector);
  std::cout << '\n';
}
