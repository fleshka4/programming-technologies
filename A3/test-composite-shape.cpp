#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

BOOST_AUTO_TEST_SUITE(test_composite_shape)

const double RADIUS = 32.5;
const double HEIGHT = 4.5;
const double WIDTH = 3.4;
const double COEFFICIENT = 2.0;
const double EPSILON = 0.000001;
const double AREA_CIRCLE = M_PI * RADIUS * RADIUS;
const double AREA_RECTANGLE = HEIGHT * WIDTH;
const double AREA = AREA_CIRCLE + AREA_RECTANGLE;
const int SIZE = 2;
const sechko::point_t CENTER_CIRCLE = {32.54, 64.38};
const sechko::point_t CENTER_RECTANGLE = {45.23, 86.43};
const sechko::point_t CENTER = CENTER_CIRCLE;
const sechko::point_t TARGET = {39.3, 95.49};

struct fixture {
  sechko::Shape::Pointer circlePtr;
  sechko::Shape::Pointer rectanglePtr;
  sechko::CompositeShape shapes;
  fixture():
    circlePtr(std::make_shared<sechko::Circle>(sechko::Circle(CENTER_CIRCLE, RADIUS))),
    rectanglePtr(std::make_shared<sechko::Rectangle>(sechko::Rectangle(CENTER_RECTANGLE, WIDTH, HEIGHT)))
  {
    shapes.add(circlePtr);
    shapes.add(rectanglePtr);
  }
};

BOOST_FIXTURE_TEST_CASE(correct_composite_shape_getters, fixture)
{
  BOOST_CHECK_CLOSE(shapes.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_EQUAL(shapes.size(), SIZE);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, CENTER.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_composite_shape, fixture)
{
  BOOST_REQUIRE_EQUAL(shapes[0], circlePtr);
  BOOST_REQUIRE_EQUAL(shapes[1], rectanglePtr);
}

BOOST_FIXTURE_TEST_CASE(correct_constructors, fixture)
{
  sechko::CompositeShape copy(shapes);
  BOOST_CHECK_EQUAL(shapes.size(), copy.size());
  for (size_t i = 0; i < shapes.size(); i++) {
    BOOST_CHECK_EQUAL(shapes[i], copy[i]);
  }

  sechko::CompositeShape moved(std::move(copy));
  BOOST_CHECK_EQUAL(moved.size(), shapes.size());
  BOOST_CHECK_EQUAL(copy.size(), 0);
  for (size_t i = 0; i < shapes.size(); i++) {
    BOOST_CHECK_EQUAL(shapes[i], moved[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(correct_assignment_operators, fixture)
{
  sechko::CompositeShape copy = shapes;
  BOOST_CHECK_EQUAL(shapes.size(), copy.size());
  for (size_t i = 0; i < shapes.size(); i++) {
    BOOST_CHECK_EQUAL(shapes[i], copy[i]);
  }

  sechko::CompositeShape moved = std::move(copy);
  BOOST_CHECK_EQUAL(moved.size(), shapes.size());
  BOOST_CHECK_EQUAL(copy.size(), 0);
  for (size_t i = 0; i < shapes.size(); i++) {
    BOOST_CHECK_EQUAL(shapes[i], moved[i]);
  }
}

BOOST_FIXTURE_TEST_CASE(correct_composite_shape_remove, fixture)
{
  BOOST_CHECK_NO_THROW(shapes.remove(1));
  BOOST_CHECK_THROW(shapes[1], std::out_of_range);

  const double newArea = shapes.getArea();
  BOOST_CHECK_CLOSE(newArea + AREA_RECTANGLE, AREA, EPSILON);

  BOOST_CHECK_EQUAL(shapes.size(), SIZE - 1);
}

BOOST_FIXTURE_TEST_CASE(correct_composite_shape_scale, fixture)
{
  const double area = AREA_RECTANGLE * COEFFICIENT * COEFFICIENT + AREA_CIRCLE * COEFFICIENT * COEFFICIENT;
  const sechko::point_t newCircleCenter = {CENTER.x - COEFFICIENT * (CENTER.x - CENTER_CIRCLE.x),
                                             CENTER.y - COEFFICIENT * (CENTER.y - CENTER_CIRCLE.y)};
  const sechko::point_t newRectangleCenter = {CENTER.x - COEFFICIENT * (CENTER.x - CENTER_RECTANGLE.x),
                                                CENTER.y - COEFFICIENT * (CENTER.y - CENTER_RECTANGLE.y)};
  shapes.scale(COEFFICIENT);

  BOOST_CHECK_EQUAL(shapes.size(), SIZE);
  BOOST_CHECK_CLOSE(shapes.getArea(), area, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, RADIUS * 2 * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, RADIUS * 2 * COEFFICIENT, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, CENTER.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, CENTER.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getCenter().x, newCircleCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes[0]->getCenter().y, newCircleCenter.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getCenter().x, newRectangleCenter.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes[1]->getCenter().y, newRectangleCenter.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_composite_shape_move_to_point, fixture)
{
  shapes.move(TARGET);

  BOOST_CHECK_EQUAL(shapes.size(), SIZE);
  BOOST_CHECK_CLOSE(shapes.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(correct_composite_shape_move_dx_dy, fixture)
{
  shapes.move(TARGET.x, TARGET.y);

  BOOST_CHECK_EQUAL(shapes.size(), SIZE);
  BOOST_CHECK_CLOSE(shapes.getArea(), AREA, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getCenter().y, CENTER.y + TARGET.y, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().height, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().width, RADIUS * 2, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.x, CENTER.x + TARGET.x, EPSILON);
  BOOST_CHECK_CLOSE(shapes.getFrameRect().pos.y, CENTER.y + TARGET.y, EPSILON);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_coefficient, fixture)
{
  BOOST_CHECK_THROW(shapes.scale(0), std::invalid_argument);
  BOOST_CHECK_THROW(shapes.scale(-COEFFICIENT), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_index, fixture)
{
  BOOST_CHECK_THROW(shapes[2], std::out_of_range);
  BOOST_CHECK_THROW(shapes[-2], std::out_of_range);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_add, fixture)
{
  std::shared_ptr<sechko::CompositeShape> compositeShape = std::make_shared<sechko::CompositeShape>(shapes);
  BOOST_CHECK_THROW(compositeShape->add(compositeShape), std::logic_error);

  BOOST_CHECK_THROW(shapes.add(circlePtr), std::logic_error);
  BOOST_CHECK_THROW(shapes.add(rectanglePtr), std::logic_error);

  BOOST_CHECK_THROW(shapes.add(nullptr), std::invalid_argument);
}

BOOST_FIXTURE_TEST_CASE(test_invalid_remove, fixture)
{
  BOOST_CHECK_THROW(shapes.remove(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_create_empty_composite_shape)
{
  sechko::CompositeShape composite;
  const sechko::rectangle_t rectangle = composite.getFrameRect();

  BOOST_CHECK_EQUAL(rectangle.height, 0);
  BOOST_CHECK_EQUAL(rectangle.width, 0);
  BOOST_CHECK_EQUAL(rectangle.pos.x, 0);
  BOOST_CHECK_EQUAL(rectangle.pos.y, 0);
  BOOST_CHECK_EQUAL(composite.size(), 0);
  BOOST_CHECK_EQUAL(composite.getArea(), 0);
  BOOST_CHECK_EQUAL(composite.getCenter().x, 0);
  BOOST_CHECK_EQUAL(composite.getCenter().y, 0);
  BOOST_CHECK_THROW(composite[0], std::out_of_range);
  BOOST_CHECK_THROW(composite.scale(COEFFICIENT), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()
