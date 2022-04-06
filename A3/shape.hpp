#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <ostream>
#include <memory>

namespace sechko {
  struct point_t;
  struct rectangle_t;

  class Shape {
  public:
    using Pointer = std::shared_ptr<Shape>;

    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual point_t getCenter() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t& point) = 0;
    virtual void print(std::ostream& ostream) const = 0;
    virtual void scale(double coefficient) = 0;
  };
}

#endif
