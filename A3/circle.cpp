#include "circle.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <stdexcept>

sechko::Circle::Circle(const point_t& point, double radius):
  point_(point),
  radius_(radius)
{
  if (radius_ <= 0) {
    throw std::invalid_argument("Invalid radius: it must be positive!");
  }
}

double sechko::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

sechko::point_t sechko::Circle::getCenter() const
{
  return point_;
}

double sechko::Circle::getRadius() const
{
  return radius_;
}

sechko::rectangle_t sechko::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, point_};
}

void sechko::Circle::move(const point_t& point)
{
  point_ = point;
}

void sechko::Circle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void sechko::Circle::print(std::ostream& ostream) const
{
  ostream << "Circle{point_.x=" << point_.x << ", point.y="
          << point_.y << ", radius_=" << radius_ << "}";
}
void sechko::Circle::scale(double coefficient)
{
  if (coefficient <= 0) {
    throw std::invalid_argument("Invalid coefficient: it must be positive!");
  }
  radius_ *= coefficient;
}
