#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace sechko {
  class Rectangle : public Shape {
  public:
    Rectangle(const point_t& point, double width, double height);
    double getArea() const override;
    point_t getCenter() const override;
    double getWidth() const;
    double getHeight() const;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(double dx, double dy) override;
    void print(std::ostream& ostream) const override;
    void scale(double coefficient) override;

  private:
    point_t point_;
    double width_;
    double height_;
  };
}

#endif
