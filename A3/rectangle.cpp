#include "rectangle.hpp"
#include <stdexcept>

sechko::Rectangle::Rectangle(const point_t& point, double width, double height):
  point_(point),
  width_(width),
  height_(height)
{
  if ((width_ <= 0) || (height_ <= 0)) {
    throw std::invalid_argument("Invalid argument(s): the measurements must be positive!");
  }
}

double sechko::Rectangle::getArea() const
{
  return width_ * height_;
}

sechko::point_t sechko::Rectangle::getCenter() const
{
  return point_;
}

double sechko::Rectangle::getWidth() const
{
  return width_;
}
double sechko::Rectangle::getHeight() const
{
  return height_;
}

sechko::rectangle_t sechko::Rectangle::getFrameRect() const
{
  return {width_, height_, point_};
}

void sechko::Rectangle::move(const point_t& point)
{
  point_ = point;
}

void sechko::Rectangle::move(double dx, double dy)
{
  point_.x += dx;
  point_.y += dy;
}

void sechko::Rectangle::print(std::ostream& ostream) const
{
  ostream << "Rectangle{point_.x=" << point_.x << ", point.y="
          << point_.y << ", width_=" << width_
          << ", height_=" << height_ << "}";
}
void sechko::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0) {
    throw std::invalid_argument("Invalid coefficient: it must be positive!");
  }
  width_ *= coefficient;
  height_ *= coefficient;
}
