#include <iostream>
#include <stdexcept>
#include "base-types.hpp"
#include "circle.hpp"
#include "rectangle.hpp"

int main()
{
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed;

  const point_t point = {78.45, -695.365};
  const double width = 3.4;
  const double height = 4.5;
  Shape* shape;
  try {
    Rectangle rectangle(point, width, height);
    shape = &rectangle;
    shape->print(std::cout);
    std::cout << "Area:" << shape->getArea() << '\n';

    const double dx = 92.49;
    const double dy = -85.555;
    shape->move(dx, dy);
    shape->print(std::cout);

    const point_t delta = {4323.545, -49349.232};
    shape->move(delta);
    shape->print(std::cout);

    std::cout << "for this rectangle width:" << shape->getFrameRect().width
              << ", height:" << shape->getFrameRect().height << ", position.x:"
              << shape->getFrameRect().pos.x << ", position.y:" << shape->getFrameRect().pos.y << '\n';
  } catch (const std::invalid_argument& exception) {
    std::cerr << exception.what();
    return 1;
  }

  const point_t point2 = {4.0, 56.12};
  const double radius = 64.48;
  try {
    Circle circle(point2, radius);
    shape = &circle;
    shape->print(std::cout);
    std::cout << "Area:" << shape->getArea() << '\n';

    const double dx = 43.56;
    const double dy = 95.6534;
    shape->move(dx, dy);
    shape->print(std::cout);

    const point_t delta2 = {5, 5};
    shape->move(delta2);
    shape->print(std::cout);

    std::cout << "for this Circle width:" << shape->getFrameRect().width
              << ", height:" << shape->getFrameRect().height << ", position.x:"
              << shape->getFrameRect().pos.x << ", position.y:" << shape->getFrameRect().pos.y << '\n';
  } catch (const std::invalid_argument& exception) {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}
