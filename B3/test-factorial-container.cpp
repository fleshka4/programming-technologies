#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "factorial-container.hpp"

BOOST_AUTO_TEST_SUITE(test_factorial_container)

const FactorialContainer factorialContainer(10);

BOOST_AUTO_TEST_CASE(correct_begin_end)
{
  const auto begin = factorialContainer.begin();
  BOOST_CHECK_EQUAL(*begin, 1);

  const size_t tenFactorial = 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10;

  const auto end = --factorialContainer.end();
  BOOST_CHECK_EQUAL(*end, tenFactorial);

  const auto rbegin = factorialContainer.rbegin();
  BOOST_CHECK_EQUAL(*rbegin, tenFactorial);

  const auto rend = --factorialContainer.rend();
  BOOST_CHECK_EQUAL(*rend, 1);
}

BOOST_AUTO_TEST_CASE(out_of_bounds)
{
  BOOST_CHECK_THROW(*(--factorialContainer.begin()), std::out_of_range);
  BOOST_CHECK_THROW(*(++factorialContainer.end()), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(overflow)
{
  BOOST_CHECK_THROW(getFactorial(21), std::overflow_error);
}

BOOST_AUTO_TEST_CASE(empty_container)
{
  const FactorialContainer empty;
  BOOST_CHECK(empty.begin() == empty.end());
  BOOST_CHECK(empty.rbegin() == empty.rend());

  BOOST_CHECK_THROW(*(--empty.begin()), std::out_of_range);
  BOOST_CHECK_THROW(*(--empty.end()), std::out_of_range);
  BOOST_CHECK_THROW(*(++empty.begin()), std::out_of_range);
  BOOST_CHECK_THROW(*(++empty.end()), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
