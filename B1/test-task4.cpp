#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"
#include "utilities.hpp"


const int SIZE = 5;

BOOST_AUTO_TEST_SUITE(test_task4)

struct fixture {
  std::streambuf* streamOut;
  std::stringstream stringStream;

  fixture():
    streamOut(std::cout.rdbuf(stringStream.rdbuf()))
  {}

  void refresh() const
  {
    std::cout.rdbuf(streamOut);
  }
};

BOOST_AUTO_TEST_CASE(correct_filling)
{
  std::vector<double> vector(SIZE);
  fillRandom(vector.data(), SIZE);
  for (int i = 0; i < SIZE; ++i) {
    BOOST_CHECK((vector[i] > -1.0) && (vector[i] < 1.0));
  }

  std::vector<double> vector2(SIZE);
  fillRandom(vector2.data(), SIZE);
  for (int i = 0; i < SIZE; ++i) {
    BOOST_CHECK((vector2[i] > -1.0) && (vector2[i] < 1.0));
  }

  BOOST_CHECK(vector != vector2);
}

BOOST_FIXTURE_TEST_CASE(correct_ascending, fixture)
{
  doFourthTask(getComparator<double>("ascending"), SIZE);

  std::vector<double> out;
  for (int i = 0; i < SIZE * 2; ++i) {
    double temp;
    stringStream >> temp;
    BOOST_CHECK((temp > -1.0) && (temp < 1.0));
    if (i >= SIZE) {
      out.push_back(temp);
    }
  }

  BOOST_CHECK(std::is_sorted(out.begin(), out.end(), getComparator<double>("descending")));
  refresh();
}

BOOST_FIXTURE_TEST_CASE(correct_descending, fixture)
{
  doFourthTask(getComparator<double>("descending"), SIZE);

  std::vector<double> out;
  for (int i = 0; i < SIZE * 2; ++i) {
    double temp;
    stringStream >> temp;
    BOOST_CHECK((temp > - 1.0) && (temp < 1.0));
    if (i >= SIZE) {
      out.push_back(temp);
    }
  }

  BOOST_CHECK(std::is_sorted(out.begin(), out.end(), getComparator<double>("ascending")));
  refresh();
}

BOOST_AUTO_TEST_CASE(test_invalid_size)
{
  BOOST_CHECK_THROW(doFourthTask(getComparator<double>("descending"), 0), std::invalid_argument);
  BOOST_CHECK_THROW(doFourthTask(getComparator<double>("descending"), -1), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
