#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape {
public:
  Circle(const point_t& point, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& point) override;
  void move(double dx, double dy) override;
  void print(std::ostream& ostream) const override;

private:
  point_t point_;
  double radius_;
};

#endif
