#include "shape.hpp"

#include <algorithm>
#include <cmath>
#include <iterator>
#include <boost/io/ios_state.hpp>

#include "utility.hpp"

std::istream& operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  boost::io::ios_flags_saver saver(in);

  char symbol;
  in >> std::noskipws >> skipWS >> symbol;
  if ((!in) || (symbol != details::OPENING_BRACE)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  int x;
  in >> skipWS >> x >> skipWS >> symbol;
  if ((!in) || (symbol != details::SEPARATOR)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  int y;
  in >> skipWS >> y >> skipWS >> symbol;
  if ((!in) || (symbol != details::CLOSING_BRACE)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  point = {x, y};
  return in;
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }

  boost::io::ios_flags_saver saver(in);

  size_t vertices;
  in >> std::noskipws >> std::ws >> vertices;
  if ((!in) || (vertices == 0)) {
    in.setstate(std::ios::failbit);
    return in;
  }

  Shape temp(vertices);
  for (auto& i : temp) {
    if (!(in >> skipWS >> i)) {
      return in;
    }
  }

  in >> skipWS;
  if ((!in.eof()) && (in.peek() != '\r') && (in.peek() != '\n')) {
    in.setstate(std::ios::failbit);
    return in;
  }

  shape = std::move(temp);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry) {
    out << details::OPENING_BRACE << point.x << details::SEPARATOR << point.y << details::CLOSING_BRACE;
  }
  return out;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sentry(out);
  if (sentry) {
    out << shape.size() << ' ';
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  }
  return out;
}

size_t details::getSquaredDistance(const Point& point, const Point& point2)
{
  return ((point.x - point2.x) * (point.x - point2.x)) + ((point.y - point2.y) * (point.y - point2.y));
}

bool isTriangle(const Shape& shape)
{
  return shape.size() == details::TRIANGLE_SIZE;
}

bool isRectangle(const Shape& shape)
{
  return (shape.size() == details::QUADRANGLE_SIZE)
      && (details::getSquaredDistance(shape[0], shape[1]) == details::getSquaredDistance(shape[2], shape[3]))
      && (details::getSquaredDistance(shape[1], shape[2]) == details::getSquaredDistance(shape[0], shape[3]))
      && (details::getSquaredDistance(shape[0], shape[2]) == details::getSquaredDistance(shape[1], shape[3]));
}

bool isSquare(const Shape& shape)
{
  return isRectangle(shape) && (details::getSquaredDistance(shape[0], shape[1]) == details::getSquaredDistance(shape[1], shape[2]));
}

bool isPentagon(const Shape& shape)
{
  return shape.size() == details::PENTAGON_SIZE;
}

bool ShapesComparator::operator()(const Shape& lhs, const Shape& rhs)
{
  if ((lhs.size() == details::QUADRANGLE_SIZE) && (rhs.size() == details::QUADRANGLE_SIZE)) {
    return isSquare(lhs) && !isSquare(rhs);
  }
  return lhs.size() < rhs.size();
}
