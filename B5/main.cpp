#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <unordered_set>

#include "shape.hpp"

void doFirstTask(std::istream& in, std::ostream& out);
void doSecondTask(std::istream& in, std::ostream& out);

int main(int argc, char* argv[])
{
  std::ios::sync_with_stdio(false);
  if (argc != 2) {
    std::cerr << "Incorrect number of arguments!";
    return 1;
  }

  std::istringstream taskNumber(argv[1]);
  unsigned int number;

  taskNumber >> number;
  if (!taskNumber.eof()) {
    std::cerr << "Fail with reading number of task!";
    return 1;
  }

  switch (number) {
    case 1:
      try {
        doFirstTask(std::cin, std::cout);
      } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 2;
      } catch (const std::exception& e) {
        std::cerr << e.what();
        return 3;
      }
      break;
    case 2:
      try {
        doSecondTask(std::cin, std::cout);
      } catch (const std::runtime_error& e) {
        std::cerr << e.what();
        return 2;
      } catch (const std::exception& e) {
        std::cerr << e.what();
        return 3;
      }
      break;
    default:
      std::cerr << "Invalid number of task\n";
      return 1;
  }

  return 0;
}

void doFirstTask(std::istream& in, std::ostream& out)
{
  std::unordered_set<std::string> words{std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()};
  if (!in.eof()) {
    throw std::runtime_error("Input error!");
  }

  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(out, "\n"));
}

void doSecondTask(std::istream& in, std::ostream& out)
{
  std::list<Shape> shapes{std::istream_iterator<Shape>(in), std::istream_iterator<Shape>()};

  if (!in.eof()) {
    throw std::runtime_error("Input error!");
  }

  const size_t verticesNumber = std::accumulate(shapes.begin(), shapes.end(), 0,
      [](size_t count, const Shape& shape)
      {
        return count += shape.size();
      });
  const size_t trianglesNumber = std::count_if(shapes.begin(), shapes.end(), &isTriangle);
  const size_t squaresNumber = std::count_if(shapes.begin(), shapes.end(), &isSquare);
  const size_t rectanglesNumber = std::count_if(shapes.begin(), shapes.end(), &isRectangle);

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), &isPentagon), shapes.end());

  std::vector<Point> points(shapes.size());

  std::transform(shapes.begin(), shapes.end(), points.begin(),
      [](const Shape& shape)
      {
        return shape[0];
      });
  shapes.sort(ShapesComparator());

  out << "Vertices: " << verticesNumber << "\nTriangles: " << trianglesNumber
      << "\nSquares: " << squaresNumber << "\nRectangles: " << rectanglesNumber << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
