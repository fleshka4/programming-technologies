#include <iostream>
#include <memory>
#include <stdexcept>
#include "base-types.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed;

  sechko::CompositeShape compositeShape;
  const sechko::point_t point = {78.45, -695.365};
  const double width = 3.4;
  const double height = 4.5;
  std::shared_ptr<sechko::Shape> shape;

  try {
    shape = std::make_shared<sechko::Rectangle>(point, width, height);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  }

  shape->print(std::cout);

  const double coefficient = 2.5;
  try {
    shape->scale(coefficient);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  }

  std::cout << "\nAfter scaling: ";
  shape->print(std::cout);
  std::cout << ", Area:" << shape->getArea() << '\n';

  try {
    compositeShape.add(shape);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what();
    return 1;
  }

  const sechko::point_t point2 = {4.0, 56.12};
  const double radius = 64.48;

  try {
    shape = std::make_shared<sechko::Circle>(point2, radius);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  }

  shape->print(std::cout);

  try {
    shape->scale(coefficient);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  }

  std::cout << "\nAfter scaling: ";
  shape->print(std::cout);
  std::cout << ", Area:" << shape->getArea() << '\n';

  try {
    compositeShape.add(shape);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what();
    return 1;
  }

  compositeShape.print(std::cout);
  std::cout << "Area of CompositeShape:" << compositeShape.getArea() << '\n';

  const double dx3 = 49.09;
  const double dy3 = 43.96;
  compositeShape.move(dx3, dy3);
  compositeShape.print(std::cout);

  const sechko::point_t point3 = {4323.567, 5402.5456};
  compositeShape.move(point3);
  compositeShape.print(std::cout);

  try {
    compositeShape.scale(coefficient);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what();
    return 1;
  } catch (const std::logic_error& e) {
    std::cerr << e.what();
    return 1;
  }

  std::cout << "After scaling: ";
  compositeShape.print(std::cout);
  std::cout << ", Area:" << compositeShape.getArea() << '\n';

  std::cout << "For this CompositeShape width:" << compositeShape.getFrameRect().width
            << ", height:" << compositeShape.getFrameRect().height << ", position.x:"
            << compositeShape.getFrameRect().pos.x << ", position.y:"
            << compositeShape.getFrameRect().pos.y << '\n';
  try {
    compositeShape.remove(1);
  } catch (const std::out_of_range& e) {
    std::cerr << e.what();
    return 1;
  }

  std::cout << "After removing: ";
  compositeShape.print(std::cout);
  return 0;
}
