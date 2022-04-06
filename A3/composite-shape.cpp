#include "composite-shape.hpp"
#include <algorithm>
#include <limits>
#include <stdexcept>
#include "base-types.hpp"

sechko::CompositeShape::CompositeShape():
  size_(0)
{}

sechko::CompositeShape::CompositeShape(const sechko::CompositeShape& rhs):
  size_(rhs.size_)
{
  if (rhs.size_ != 0) {
    shapes_ = std::make_unique<Pointer[]>(rhs.size_);
    for (size_t i = 0; i < rhs.size_; ++i) {
      shapes_[i] = rhs.shapes_[i];
    }
  }
}

sechko::CompositeShape::CompositeShape(sechko::CompositeShape&& rhs) noexcept:
  size_(rhs.size_),
  shapes_(std::move(rhs.shapes_))
{
  rhs.size_ = 0;
}

sechko::CompositeShape& sechko::CompositeShape::operator=(const sechko::CompositeShape& rhs)
{
  if (this != &rhs) {
    CompositeShape temp(rhs);
    swap(temp);
  }
  return *this;
}

sechko::CompositeShape& sechko::CompositeShape::operator=(sechko::CompositeShape&& rhs) noexcept
{
  if (this != &rhs) {
    shapes_ = std::move(rhs.shapes_);
    size_ = rhs.size_;
    rhs.size_ = 0;
  }
  return *this;
}

sechko::Shape::Pointer sechko::CompositeShape::operator[](size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("Wrong index!");
  }
  return shapes_[index];
}

void sechko::CompositeShape::add(const sechko::Shape::Pointer& shape)
{
  if (!shape) {
    throw std::invalid_argument("Empty shape cannot be added!");
  }
  if (this == shape.get()) {
    throw std::logic_error("You cannot add composite shape to itself!");
  }
  for (size_t i = 0; i < size_; ++i) {
    if (shape == shapes_[i]) {
      throw std::logic_error("You cannot add shape that is already here!");
    }
  }
  std::unique_ptr<Shape::Pointer[]> temp(std::make_unique<Pointer[]>(size_ + 1));
  for (size_t i = 0; i < size_; ++i) {
    temp[i] = shapes_[i];
  }
  temp[size_++] = shape;
  shapes_ = std::move(temp);
}

double sechko::CompositeShape::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; ++i) {
    area += shapes_[i]->getArea();
  }
  return area;
}

sechko::point_t sechko::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

sechko::rectangle_t sechko::CompositeShape::getFrameRect() const
{
  if (size_ == 0) {
    return {0, 0, {0, 0}};
  }
  double minX = std::numeric_limits<double>::max();
  double maxX = std::numeric_limits<double>::lowest();
  double minY = minX;
  double maxY = maxX;

  for (size_t i = 0; i < size_; ++i) {
    const rectangle_t rectangle = shapes_[i]->getFrameRect();
    if ((rectangle.width == 0) || (rectangle.height == 0)) {
      continue;
    }
    minX = std::min(minX, rectangle.pos.x - rectangle.width / 2);
    maxX = std::max(maxX, rectangle.pos.x + rectangle.width / 2);
    minY = std::min(minY, rectangle.pos.y - rectangle.height / 2);
    maxY = std::max(maxY, rectangle.pos.y + rectangle.height / 2);
  }
  if (minX == std::numeric_limits<double>::max()) {
    return {0, 0, {0, 0}};
  }
  return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
}

size_t sechko::CompositeShape::size() const
{
  return size_;
}

void sechko::CompositeShape::swap(sechko::CompositeShape& rhs) noexcept
{
  std::swap(size_, rhs.size_);
  std::swap(shapes_, rhs.shapes_);
}

void sechko::CompositeShape::move(double dx, double dy)
{
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->move(dx, dy);
  }
}

void sechko::CompositeShape::move(const sechko::point_t& point)
{
  move(point.x - getFrameRect().pos.x , point.y - getFrameRect().pos.y);
}

void sechko::CompositeShape::print(std::ostream& ostream) const
{
  if (size_ == 0) {
    ostream << "CompositeShape{shapes_=[], size_=0}";
    return;
  }
  ostream << "CompositeShape{shapes_=[";
  for (size_t i = 0; i < size_; ++i) {
    shapes_[i]->print(ostream);
    if (i != size_ - 1) {
      ostream << ", ";
    }
  }
  ostream << "], size_=" << size_ << "}\n";
}

void sechko::CompositeShape::scale(double coefficient)
{
  if (size_ == 0) {
    throw std::logic_error("Composite shape does not exist!");
  }
  if (coefficient <= 0) {
    throw std::invalid_argument("Invalid coefficient: it must be positive!");
  }
  const point_t center = getFrameRect().pos;
  for (size_t i = 0; i < size_; ++i) {
    const double dx = (shapes_[i]->getFrameRect().pos.x - center.x) * coefficient + center.x;
    const double dy = (shapes_[i]->getFrameRect().pos.y - center.y) * coefficient + center.y;
    shapes_[i]->move({dx, dy});
    shapes_[i]->scale(coefficient);
  }
}

void sechko::CompositeShape::remove(size_t index)
{
  if (index >= size_) {
    throw std::out_of_range("Wrong index!");
  }
  for (size_t i = index; i < size_ - 1; ++i) {
    shapes_[i] = shapes_[i + 1];
  }
  shapes_[--size_].reset();
}
