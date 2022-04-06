#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"
#include "utilities.hpp"

const std::string TEST_INPUT = "43894 94 94 0 429 423 -4 93";
const std::string ASCENDING = "-4 0 93 94 94 423 429 43894 \n"
                              "-4 0 93 94 94 423 429 43894 \n"
                              "-4 0 93 94 94 423 429 43894 \n";
const std::string DESCENDING = "43894 429 423 94 94 93 0 -4 \n"
                               "43894 429 423 94 94 93 0 -4 \n"
                               "43894 429 423 94 94 93 0 -4 \n";

BOOST_AUTO_TEST_SUITE(test_task1)

struct fixture {
  std::streambuf* streamIn;
  std::streambuf* streamOut;
  std::istringstream istringstream;
  std::ostringstream ostringstream;

  fixture():
    streamIn(std::cin.rdbuf(istringstream.rdbuf())),
    streamOut(std::cout.rdbuf(ostringstream.rdbuf()))
  {}

  void refresh() const
  {
    std::cin.rdbuf(streamIn);
    std::cout.rdbuf(streamOut);
  }
};

BOOST_AUTO_TEST_CASE(correct_sort)
{
  std::vector<int> vector = {5, 49, 43, 43, 0, -54, -32, 903};
  const std::vector<int> copy(vector);
  std::vector<int> sortBySTL(vector);

  sort<OperatorAccess>(vector, getComparator<int>("ascending"));
  BOOST_CHECK_EQUAL(vector.size(), copy.size());
  std::sort(sortBySTL.begin(), sortBySTL.end(), std::less<>());
  BOOST_CHECK(vector == sortBySTL);

  sort<OperatorAccess>(vector, getComparator<int>("descending"));
  BOOST_CHECK_EQUAL(vector.size(), copy.size());

  std::sort(sortBySTL.begin(), sortBySTL.end(), std::greater<>());
  BOOST_CHECK(vector == sortBySTL);
}

BOOST_FIXTURE_TEST_CASE(correct_ascending, fixture)
{
  istringstream.str(TEST_INPUT);
  doFirstTask(getComparator<int>("ascending"));
  const std::string output = ostringstream.str();
  refresh();
  BOOST_CHECK_EQUAL(output, ASCENDING);
}

BOOST_FIXTURE_TEST_CASE(correct_descending, fixture)
{
  istringstream.str(TEST_INPUT);
  doFirstTask(getComparator<int>("descending"));
  const std::string output = ostringstream.str();
  refresh();
  BOOST_CHECK_EQUAL(output, DESCENDING);
}

BOOST_AUTO_TEST_CASE(test_invalid_order)
{
  BOOST_CHECK_THROW(doFirstTask(getComparator<int>(nullptr)), std::invalid_argument);
  BOOST_CHECK_THROW(doFirstTask(getComparator<int>("abcdefghijklmn")), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_symbols_in_stream, fixture)
{
  const std::string inputChar = "3 fj 93 kd\n";
  istringstream.str(inputChar);
  std::cout.rdbuf(streamOut);
  BOOST_CHECK_THROW(doFirstTask(getComparator<int>("ascending")), std::invalid_argument);

  const std::string inputDouble = "3 5.65 93 9.64321\n";
  istringstream.str(inputDouble);
  std::cout.rdbuf(streamOut);
  BOOST_CHECK_THROW(doFirstTask(getComparator<int>("ascending")), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
