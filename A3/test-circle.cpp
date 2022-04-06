#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"
#include "circle.hpp"

BOOST_AUTO_TEST_SUITE(test_circle)

const double RADIUS = 32.5;
const double COEFFICIENT = 2.5;
const double EPSILON = 0.000001;
const double AREA = M_PI * RADIUS * RADIUS;
const sechko::point_t CENTER = {5.0, 4.5};
const sechko::point_t TARGET = {43.49, 98.54};

struct fixture {
  sechko::Circle circle;
  fixture():
    circle(CENTER, RADIUS)
  {}
};

BOOST_FIXTURE_TEST_CASE(correct_circle_getters, fixture)
{
  BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_circle_move_to_point, fixture)
{
  circle.move(TARGET);
  BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().y, TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_circle_move_dx_dy, fixture)
{
  circle.move(TARGET.x, TARGET.y);
  BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTER.y + TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y + TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_circle_scale, fixture)
{
  circle.scale(COEFFICIENT);
  BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getArea(), AREA * COEFFICIENT * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * COEFFICIENT * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * COEFFICIENT * 2, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_coefficient, fixture)
{
  BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(circle.scale(-COEFFICIENT), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(test_invalid_radius)
{
  BOOST_CHECK_THROW(sechko::Circle circle(CENTER, 0), std::invalid_argument);
  BOOST_CHECK_THROW(sechko::Circle circle(CENTER, -RADIUS), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
