#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace sechko {
  class CompositeShape : public Shape {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& rhs);
    CompositeShape(CompositeShape&& rhs) noexcept;
    ~CompositeShape() override = default;
    CompositeShape& operator=(const CompositeShape& rhs);
    CompositeShape& operator=(CompositeShape&& rhs) noexcept;
    Pointer operator[](size_t index);
    void add(const Pointer& shape);
    void remove(size_t index);
    double getArea() const override;
    point_t getCenter() const override;
    rectangle_t getFrameRect() const override;
    size_t size() const;
    void swap(CompositeShape& rhs) noexcept;
    void move(double dx, double dy) override;
    void move(const point_t& point) override;
    void print(std::ostream& ostream) const override;
    void scale(double coefficient) override;

  private:
    size_t size_;
    std::unique_ptr<Shape::Pointer[]> shapes_;
  };
}

#endif
