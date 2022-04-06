#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>

struct Point {
  int x, y;
};

using Shape = std::vector<Point>;

namespace details {
  const char OPENING_BRACE = '(';
  const char CLOSING_BRACE = ')';
  const char SEPARATOR = ';';
  const unsigned int TRIANGLE_SIZE = 3;
  const unsigned int QUADRANGLE_SIZE = 4;
  const unsigned int PENTAGON_SIZE = 5;

  size_t getSquaredDistance(const Point& point, const Point& point2);
}

struct ShapesComparator {
  bool operator()(const Shape& lhs, const Shape& rhs);
};

std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Shape& shape);

std::ostream& operator<<(std::ostream& out, const Point& point);
std::ostream& operator<<(std::ostream& out, const Shape& shape);

bool isTriangle(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);
bool isPentagon(const Shape& shape);

#endif
