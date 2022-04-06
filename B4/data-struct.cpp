#include "data-struct.hpp"

#include <iostream>
#include <boost/io/ios_state.hpp>
#include "utility.hpp"

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  std::istream::sentry sentry(in);

  if (!sentry) {
    return in;
  }

  boost::io::ios_flags_saver saver(in);
  const char SEPARATOR = ',';
  const int MAX_VALUE = 5;

  int key1;
  in >> std::noskipws >> std::ws >> key1;

  if ((!in) || (std::abs(key1) > MAX_VALUE)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  char symbol;
  in >> symbol;
  if ((!in) || (symbol != SEPARATOR)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  int key2;
  in >> skipWS >> key2;

  if ((!in) || (std::abs(key2) > MAX_VALUE)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> symbol;
  if ((!in) || (symbol != SEPARATOR)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> skipWS;

  std::string str;
  std::getline(in, str);

  if ((!in) || (str.empty())) {
    in.setstate(std::ios::failbit);
    return in;
  }

  dataStruct = {key1, key2, str};
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(out);

  if (sentry) {
    const char SEPARATOR = ',';
    out << dataStruct.key1 << SEPARATOR << dataStruct.key2 << SEPARATOR << dataStruct.str;
  }
  return out;
}

bool DataStructComparator::operator()(const DataStruct& lhs, const DataStruct& rhs) const
{
  if (lhs.key1 != rhs.key1) {
    return lhs.key1 < rhs.key1;
  }
  if (lhs.key2 != rhs.key2) {
    return lhs.key2 < rhs.key2;
  }
  return lhs.str.size() < rhs.str.size();
}
