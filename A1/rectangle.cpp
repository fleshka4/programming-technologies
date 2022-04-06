#include "rectangle.hpp"
#include <stdexcept>

Rectangle::Rectangle(const point_t& point, double width, double height):
  point_(point),
  width_(width),
  height_(height)
{
  if ((width_ <= 0) || (height_ <= 0)) {
    throw std::invalid_argument("Invalid argument(s): the measurements must be positive!");
  }
}

double Rectangle::getArea() const
{
  return width_ * height_;
}

rectangle_t Rectangle::getFrameRect() const
{
  return {width_, height_, point_};
}

void Rectangle::move(const point_t& point)
{
  point_ = point;
}

void Rectangle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void Rectangle::print(std::ostream& ostream) const
{
  ostream << "Rectangle{point_.x=" << point_.x << ", point.y="
          << point_.y << ", width_=" << width_
          << ", height_=" << height_ << "}\n";
}
