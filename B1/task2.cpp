#include <cstdlib>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <vector>
#include "tasks.hpp"
#include "utilities.hpp"

void doSecondTask(const char* filename)
{
  if (filename == nullptr) {
    throw std::invalid_argument("Filename is empty!");
  }

  std::ifstream fin(filename);
  if (!fin) {
    throw std::runtime_error("File cannot be opened!");
  }
  if (fin.peek() == EOF) {
    return;
  }

  size_t size = 0;
  size_t capacity = 15;
  std::unique_ptr<char[], decltype(&free)> arr(static_cast<char*>(malloc(capacity)), free);

  if (!arr) {
    throw std::bad_alloc();
  }

  while (fin) {
    fin.read(arr.get() + size, capacity - size);
    size += fin.gcount();

    if (size == capacity) {
      capacity *= 2;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char*>(realloc(arr.get(), capacity)), free);

      if (!temp) {
        throw std::bad_alloc();
      }

      arr.release();
      arr = std::move(temp);
    }
  }

  std::vector<char> vector(arr.get(), arr.get() + size);
  print(vector, "");
}
