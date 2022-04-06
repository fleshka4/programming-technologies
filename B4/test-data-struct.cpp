#include <iostream>
#include <boost/test/unit_test.hpp>
#include "data-struct.hpp"

BOOST_AUTO_TEST_SUITE(test_data_struct)

struct fixture {
  DataStruct dataStruct;
  std::istringstream in;
};

BOOST_FIXTURE_TEST_CASE(correct_input_output, fixture)
{
  in.str("2,-1,ifsfhopr");
  in >> dataStruct;
  BOOST_CHECK_EQUAL(dataStruct.key1, 2);
  BOOST_CHECK_EQUAL(dataStruct.key2, -1);
  BOOST_CHECK_EQUAL(dataStruct.str, "ifsfhopr");
  std::ostringstream out;
  out << dataStruct;
  BOOST_CHECK_EQUAL(out.str(), "2,-1,ifsfhopr");
  in.clear();

  in.str("    5,                    1,    \t      hcgjslkjfo");
  in >> dataStruct;
  BOOST_CHECK_EQUAL(dataStruct.key1, 5);
  BOOST_CHECK_EQUAL(dataStruct.key2, 1);
  BOOST_CHECK_EQUAL(dataStruct.str, "hcgjslkjfo");
  std::ostringstream out2;
  out2 << dataStruct;
  BOOST_CHECK_EQUAL(out2.str(), "5,1,hcgjslkjfo");
}

BOOST_AUTO_TEST_CASE(correct_compare)
{
  DataStructComparator dataStructComparator;
  const DataStruct dataStruct1 = {1, 5, "OsdjwA"};
  const DataStruct dataStruct2 = {2, -3, "KKds"};
  BOOST_CHECK(dataStructComparator(dataStruct1, dataStruct2));

  const DataStruct dataStruct3 = {2, 5, "OsdjwA"};
  const DataStruct dataStruct4 = {2, -3, "KKds"};
  BOOST_CHECK(dataStructComparator(dataStruct4, dataStruct3));

  const DataStruct dataStruct5 = {2, -3, "OsdjwA"};
  const DataStruct dataStruct6 = {2, -3, "KKds"};
  BOOST_CHECK(dataStructComparator(dataStruct6, dataStruct5));
}

BOOST_FIXTURE_TEST_CASE(invalid_key1, fixture)
{
  in.str("6,-1,aflfo");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("-6,-1,jfkaw");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("4.33,-1,rppfld");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("-3.21,-1,alfl");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("add,-1,kolsp");
  in >> dataStruct;
  BOOST_CHECK(!in);
}

BOOST_FIXTURE_TEST_CASE(invalid_key2, fixture)
{
  in.str("2,-6,ASKAdsl");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2,6,DKSJDK");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2,4.21,defel");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2,-2.106,LJKfn");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2,store,JHDIps");
  in >> dataStruct;
  BOOST_CHECK(!in);
}

BOOST_FIXTURE_TEST_CASE(invalid_str, fixture)
{
  in.str("2,-6,Y3uR5dWeu.Q^Cx?JLpLi2vzOsZ");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2,6,");
  in >> dataStruct;
  BOOST_CHECK(!in);
}

BOOST_FIXTURE_TEST_CASE(missing_commas, fixture)
{
  in.str("2,-6 ghdr");
  in >> dataStruct;
  BOOST_CHECK(!in);
  in.clear();

  in.str("2 6, dgisfjhl");
  in >> dataStruct;
  BOOST_CHECK(!in);
}

BOOST_AUTO_TEST_SUITE_END()
