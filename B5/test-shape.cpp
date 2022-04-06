#include <sstream>
#include <boost/test/unit_test.hpp>
#include "shape.hpp"

BOOST_AUTO_TEST_SUITE(test_shape)

struct fixture {
  Point point;
  Shape shape;

  const Shape triangle = {{54, 23}, {98, 74}, {90, 85}};
  const Shape rectangle = {{0, 0}, {0, 10}, {5, 10}, {5, 0}};
  const Shape square = {{-1, -1}, {-1, -5}, {-5, -5}, {-5, -1}};
  const Shape pentagon = {{1, 6}, {4, 2}, {8, 2}, {10, 6}, {7, 11}};

  std::istringstream in;
  std::ostringstream out;
  std::ostringstream out2;
};

BOOST_FIXTURE_TEST_CASE(correct_input_output_point, fixture)
{
  in.str("(-43782 ;-9999)");
  in >> point;
  BOOST_CHECK_EQUAL(point.x, -43782);
  BOOST_CHECK_EQUAL(point.y, -9999);
  out << point;
  BOOST_CHECK_EQUAL(out.str(), "(-43782;-9999)");
  in.clear();

  in.str("(  500000 ; 3231  )");
  in >> point;
  BOOST_CHECK_EQUAL(point.x, 500000);
  BOOST_CHECK_EQUAL(point.y, 3231);
  out2 << point;
  BOOST_CHECK_EQUAL(out2.str(), "(500000;3231)");
}

BOOST_FIXTURE_TEST_CASE(correct_input_output_shape, fixture)
{
  in.str("4 (-4467; -2284) (-4467; 1581) (-1189; 1581) (-1189; -2284)");
  in >> shape;

  BOOST_CHECK_EQUAL(shape.size(), 4);

  BOOST_CHECK_EQUAL(shape[0].x, -4467);
  BOOST_CHECK_EQUAL(shape[0].y, -2284);
  BOOST_CHECK_EQUAL(shape[1].x, -4467);
  BOOST_CHECK_EQUAL(shape[1].y, 1581);
  BOOST_CHECK_EQUAL(shape[2].x, -1189);
  BOOST_CHECK_EQUAL(shape[2].y, 1581);
  BOOST_CHECK_EQUAL(shape[3].x, -1189);
  BOOST_CHECK_EQUAL(shape[3].y, -2284);

  out << shape;
  BOOST_CHECK_EQUAL(out.str(), "4 (-4467;-2284) (-4467;1581) (-1189;1581) (-1189;-2284) ");
  in.clear();

  in.str("3 (-8481; -1484) (-4228; -3787) (-8740; 1163)");
  in >> shape;

  BOOST_CHECK_EQUAL(shape.size(), 3);

  BOOST_CHECK_EQUAL(shape[0].x, -8481);
  BOOST_CHECK_EQUAL(shape[0].y, -1484);
  BOOST_CHECK_EQUAL(shape[1].x, -4228);
  BOOST_CHECK_EQUAL(shape[1].y, -3787);
  BOOST_CHECK_EQUAL(shape[2].x, -8740);
  BOOST_CHECK_EQUAL(shape[2].y, 1163);

  out2 << shape;
  BOOST_CHECK_EQUAL(out2.str(), "3 (-8481;-1484) (-4228;-3787) (-8740;1163) ");;
}

BOOST_FIXTURE_TEST_CASE(correct_compare, fixture)
{
  ShapesComparator shapesComparator;
  BOOST_CHECK(shapesComparator(triangle, rectangle));
  BOOST_CHECK(shapesComparator(triangle, pentagon));
  BOOST_CHECK(shapesComparator(square, pentagon));
  BOOST_CHECK(shapesComparator(rectangle, pentagon));
  BOOST_CHECK(shapesComparator(triangle, square));
}

BOOST_FIXTURE_TEST_CASE(invalid_input_point, fixture)
{
  in.str("( ;-9999)");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  500000 ;  )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(   ;  )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  fa[ ; 43 )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  500000 ; 4839jkd )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("  432 ; 4294284 )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  999 ; 433");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  876 , 543 )");
  in >> point;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(  500000 545  )");
  in >> point;
  BOOST_CHECK(!in);
}

BOOST_FIXTURE_TEST_CASE(invalid_input_shape, fixture)
{
  in.str("3 (-5379; -8671) (-5379; -5132) (-6916; -5132) (-6916; -8671)");
  in >> shape;
  BOOST_CHECK(!in);
  in.clear();

  in.str("3 (-5379; -8671) (-5379; -5132)");
  in >> shape;
  BOOST_CHECK(!in);
  in.clear();

  in.str("(-5379; -8671) (-5379; -5132) (-6916; -5132) (-6916; -8671)");
  in >> shape;
  BOOST_CHECK(!in);
  in.clear();

  in.str("B5 (-5379; -8671) (-5379; -5132) (-6916; -5132) (-6916; -8671)");
  in >> shape;
  BOOST_CHECK(!in);
}

BOOST_FIXTURE_TEST_CASE(correct_isTriangle, fixture)
{
  BOOST_CHECK(isTriangle(triangle));

  BOOST_CHECK(!isTriangle(rectangle));
  BOOST_CHECK(!isTriangle(square));
  BOOST_CHECK(!isTriangle(pentagon));
}

BOOST_FIXTURE_TEST_CASE(correct_isRectangle, fixture)
{
  BOOST_CHECK(isRectangle(rectangle));
  BOOST_CHECK(isRectangle(square));

  BOOST_CHECK(!isRectangle(triangle));
  BOOST_CHECK(!isRectangle(pentagon));
}

BOOST_FIXTURE_TEST_CASE(correct_isSquare, fixture)
{
  BOOST_CHECK(isSquare(square));

  BOOST_CHECK(!isSquare(triangle));
  BOOST_CHECK(!isSquare(rectangle));
  BOOST_CHECK(!isSquare(pentagon));
}

BOOST_FIXTURE_TEST_CASE(correct_isPentagon, fixture)
{
  BOOST_CHECK(isPentagon(pentagon));

  BOOST_CHECK(!isPentagon(triangle));
  BOOST_CHECK(!isPentagon(rectangle));
  BOOST_CHECK(!isPentagon(square));
}

BOOST_AUTO_TEST_SUITE_END()
