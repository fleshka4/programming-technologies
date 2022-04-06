#include <iostream>
#include <sstream>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  std::ios::sync_with_stdio(false);
  if (argc != 2) {
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
      doFirstTask();
      break;
    case 2:
      try {
        doSecondTask();
      } catch (const std::out_of_range& e) {
        std::cerr << e.what();
        return 2;
      } catch (const std::overflow_error& e) {
        std::cerr << e.what();
        return 2;
      }
      break;
    default:
      std::cerr << "Invalid number of task\n";
      return 1;
  }
}
