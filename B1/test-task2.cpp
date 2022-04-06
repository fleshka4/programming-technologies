#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(test_task2)

struct fixture {
  std::streambuf* streamOut;
  std::ostringstream ostringstream;

  fixture():
    streamOut(std::cout.rdbuf(ostringstream.rdbuf()))
  {}

  void refresh() const
  {
    std::cout.rdbuf(streamOut);
  }
};

BOOST_FIXTURE_TEST_CASE(correct_input, fixture)
{
  const char* filename = "test2.txt";
  const std::string string = "Hello world!";
  std::ofstream ofstream(filename);
  ofstream << string;
  ofstream.close();
  doSecondTask(filename);
  const std::string out = ostringstream.str();
  refresh();
  BOOST_CHECK_EQUAL(out, string);
}

BOOST_AUTO_TEST_CASE(test_invalid_filename)
{
  BOOST_CHECK_THROW(doSecondTask(nullptr), std::invalid_argument);
  BOOST_CHECK_THROW(doSecondTask("testname.txt"), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()
