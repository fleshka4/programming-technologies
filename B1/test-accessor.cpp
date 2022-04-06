#include <forward_list>
#include <stdexcept>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "accessor.hpp"

BOOST_AUTO_TEST_SUITE(test_accessor)
struct fixture {
  std::vector<int> vector;
  std::forward_list<int> list;
  fixture():
    vector({65, 32, 89, 94, 1212, 574}),
    list({34, 54, 22, 99, 903, 585})
  {}
};

BOOST_FIXTURE_TEST_CASE(correct_operator_access, fixture)
{
  BOOST_CHECK_EQUAL(0, OperatorAccess<std::vector<int>>::begin(vector));
  BOOST_CHECK_EQUAL(vector.size(), OperatorAccess<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(vector[3], OperatorAccess<std::vector<int>>::get(vector, 3));
  BOOST_CHECK_THROW(OperatorAccess<std::vector<int>>::get(vector, 6), std::out_of_range);
  BOOST_CHECK_THROW(OperatorAccess<std::vector<int>>::get(vector, -1), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(correct_at_access, fixture)
{
  const size_t index = 3;
  BOOST_CHECK_EQUAL(0, AtAccess<std::vector<int>>::begin(vector));
  BOOST_CHECK_EQUAL(vector.size(), AtAccess<std::vector<int>>::end(vector));
  BOOST_CHECK_EQUAL(vector[index], AtAccess<std::vector<int>>::get(vector, index));
  BOOST_CHECK_THROW(AtAccess<std::vector<int>>::get(vector, 6), std::out_of_range);
  BOOST_CHECK_THROW(AtAccess<std::vector<int>>::get(vector, -1), std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(correct_iterator_access, fixture)
{
  BOOST_CHECK(list.begin() == IteratorAccess<std::forward_list<int>>::begin(list));
  BOOST_CHECK(list.end() == IteratorAccess<std::forward_list<int>>::end(list));
  auto it = ++list.begin();
  BOOST_CHECK(*it == IteratorAccess<std::forward_list<int>>::get(list, it));
}

BOOST_AUTO_TEST_SUITE_END()
