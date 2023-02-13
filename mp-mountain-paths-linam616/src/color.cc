#include "color.hpp"
#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  const int kMax = 255;
  if(r < 0 || r > kMax || g < 0 || g > kMax || b < 0 || b > kMax) {
    throw std::invalid_argument("colors are out of range!");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}