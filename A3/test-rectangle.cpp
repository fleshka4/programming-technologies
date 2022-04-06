#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(test_rectangle)

const double HEIGHT = 3.4;
const double WIDTH = 4.5;
const double COEFFICIENT = 2.2;
const double EPSILON = 0.000001;
const double AREA = HEIGHT * WIDTH;
const sechko::point_t CENTER = {54.32, 88.56};
const sechko::point_t TARGET = {67.45, 39.43};

struct fixture {
  sechko::Rectangle rectangle;
  fixture():
    rectangle(CENTER, WIDTH, HEIGHT)
  {}
};

BOOST_FIXTURE_TEST_CASE(correct_rectangle_getters, fixture)
{
  BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_rectangle_move_to_point, fixture)
{
  rectangle.move(TARGET);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_rectangle_move_dx_dy, fixture)
{
  rectangle.move(TARGET.x, TARGET.y);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, CENTER.y + TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y + TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_rectangle_scale, fixture)
{
  rectangle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, HEIGHT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, WIDTH * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_coefficient, fixture)
{
  BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(rectangle.scale(-COEFFICIENT), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_radius)
{
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, 0, HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, WIDTH, 0), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, 0, 0), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, -WIDTH, HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, WIDTH, -HEIGHT), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Rectangle rectangle(CENTER, -WIDTH, -HEIGHT), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
