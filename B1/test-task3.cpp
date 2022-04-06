#include <iostream>
#include <stdexcept>
#include <string>

#include <boost/test/unit_test.hpp>

#include "tasks.hpp"

BOOST_AUTO_TEST_SUITE(test_task3)

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

BOOST_FIXTURE_TEST_CASE(correct_first_subtask, fixture)
{
  const std::string input = "43 76 89 54 1 0";
  istringstream.str(input);
  doThirdTask();
  const std::string output = ostringstream.str();

  refresh();

  const std::string expected = "43 89 1 \n";
  BOOST_CHECK_EQUAL(output, expected);
}

BOOST_FIXTURE_TEST_CASE(correct_first_subtask_without_even_numbers, fixture)
{
  const std::string input = "43 77 89 55 1 0";
  istringstream.str(input);
  doThirdTask();
  const std::string output = ostringstream.str();

  refresh();

  const std::string expected = "43 77 89 55 1 \n";
  BOOST_CHECK_EQUAL(output, expected);
}

BOOST_FIXTURE_TEST_CASE(correct_second_subtask, fixture)
{
  const std::string input = "42 76 88 54 2 0";
  istringstream.str(input);
  doThirdTask();
  const std::string output = ostringstream.str();

  refresh();

  const std::string expected = "42 1 1 1 76 88 54 1 1 1 2 \n";
  BOOST_CHECK_EQUAL(output, expected);
}

BOOST_FIXTURE_TEST_CASE(correct_second_subtask_without_fulfilled_condition, fixture)
{
  const std::string input = "43 76 88 56 2 0";
  istringstream.str(input);
  doThirdTask();
  const std::string output = ostringstream.str();

  refresh();

  const std::string expected = "43 76 88 56 2 \n";
  BOOST_CHECK_EQUAL(output, expected);
}

BOOST_FIXTURE_TEST_CASE(correct_working_without_subtasks, fixture)
{
  const std::string input = "43 77 89 55 5 0";
  istringstream.str(input);
  doThirdTask();
  const std::string output = ostringstream.str();

  refresh();

  const std::string expected = "43 77 89 55 5 \n";
  BOOST_CHECK_EQUAL(output, expected);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_symbols_in_stream, fixture)
{
  const std::string inputChar = "43 21 76 jfkdfk 89 54 30 24 dggwe 2 0";
  istringstream.str(inputChar);
  std::cout.rdbuf(streamOut);
  BOOST_CHECK_THROW(doThirdTask();, std::invalid_argument);

  const std::string inputDouble = "43 76 5.654 78.5 89.5454 54.3432 66 1 0";
  istringstream.str(inputDouble);
  std::cout.rdbuf(streamOut);
  BOOST_CHECK_THROW(doThirdTask();, std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
