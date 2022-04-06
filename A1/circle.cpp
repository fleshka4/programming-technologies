#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

Circle::Circle(const point_t& point, double radius):
  point_(point),
  radius_(radius)
{
  if (radius_ <= 0) {
    throw std::invalid_argument("Invalid radius!");
  }
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, point_};
}

void Circle::move(const point_t& point)
{
  point_ = point;
}

void Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void Circle::print(std::ostream& ostream) const
{
  ostream << "Circle{point_.x=" << point_.x << ", point.y="
          << point_.y << ", radius_=" << radius_ << "}\n";
}
