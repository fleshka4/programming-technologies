#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include "tasks.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[])
{
  std::ios::sync_with_stdio(false);
  if ((argc < 2) || (argc > 4)) {
    std::cerr << "Incorrect number of arguments!";
    return 1;
  }

  std::istringstream taskNumber(argv[1]);
  unsigned int number;

  taskNumber >> number;
  if (!taskNumber.eof()) {
    std::cerr << "Fail with reading number of task!";
    return 1;
  }

  switch (number) {
    case 1:
      if (argc != 3) {
        std::cerr << "The number of arguments must be three!";
        return 1;
      }
      try {
        doFirstTask(getComparator<int>(argv[2]));
      } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        return 1;
      } catch (const std::out_of_range& e) {
        std::cerr << e.what();
        return 1;
      }
      break;
    case 2:
      if (argc != 3) {
        std::cerr << "The number of arguments must be three!";
        return 1;
      }
      try {
        doSecondTask(argv[2]);
      } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        return 1;
      } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 2;
      } catch (const std::bad_alloc& e) {
        std::cerr << e.what();
        return 2;
      }
      break;
    case 3:
      if (argc != 2) {
        std::cerr << "The number of arguments must be two!";
        return 1;
      }
      try {
        doThirdTask();
      } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        return 1;
      } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 2;
      }
      break;
    case 4:
      if (argc != 4) {
        std::cerr << "The number of arguments must be four!";
        return 1;
      }

      try {
        std::istringstream stream(argv[3]);
        int size;
        stream >> size;
        if (!stream.eof()) {
          std::cerr << "The third argument must be a single number!";
          return 1;
        }
        doFourthTask(getComparator<double>(argv[2]), size);
      } catch (const std::invalid_argument& e) {
        std::cerr << e.what();
        return 1;
      }
      break;
    default:
      std::cerr << "Invalid number of task!";
      return 1;
  }

  return 0;
}
