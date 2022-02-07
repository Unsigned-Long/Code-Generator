/**
 * @brief cmd ['enumgenor Color red yellow green black white blue']
 */

#include <iostream>

enum class Color {
  /**
   * @brief options
   */
  RED,
  YELLOW,
  GREEN,
  BLACK,
  WHITE,
  BLUE
};
/**
 * @brief override operator '<<' for type 'Color'
 */
std::ostream &operator<<(std::ostream &os, const Color &obj) {
  switch (obj) {
    case Color::RED:
      os << "RED";
      break;
    case Color::YELLOW:
      os << "YELLOW";
      break;
    case Color::GREEN:
      os << "GREEN";
      break;
    case Color::BLACK:
      os << "BLACK";
      break;
    case Color::WHITE:
      os << "WHITE";
      break;
    case Color::BLUE:
      os << "BLUE";
      break;
  }
  return os;
};