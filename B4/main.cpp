#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "data-struct.hpp"

int main()
{
  std::ios::sync_with_stdio(false);

  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());

  if (!std::cin.eof()) {
    std::cerr << "Input error!";
    return 2;
  }

  std::sort(vector.begin(), vector.end(), DataStructComparator());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
