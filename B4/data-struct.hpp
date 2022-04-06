#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iosfwd>
#include <string>

struct DataStruct {
  int key1;
  int key2;
  std::string str;

  friend std::istream& operator>>(std::istream& in, DataStruct& dataStruct);
  friend std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);
};

struct DataStructComparator {
  bool operator()(const DataStruct& lhs, const DataStruct& rhs) const;
};

#endif
