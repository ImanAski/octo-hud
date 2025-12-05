#pragma once

#include <cstdint>

namespace pico_hud {
class Color {
public:
  /*
   * @brief Default constructor. Creates a black color.
   */
  constexpr Color() : value(0) {}

  /*
   * @brief Constructs a color from a raw 16-bit color value.
   * @param val The 16-bit color value
   */
  constexpr explicit Color(uint16_t val) : value(val) {}

  /*
   * @brief .
   * @param r value of red
   * @param g value of green
   * @param b value of blue
   */
  static constexpr Color fromRGB(uint16_t r, uint16_t g, uint16_t b) {
    uint16_t r5 = (r >> 3);
    uint16_t g6 = (g >> 2);
    uint16_t b5 = (b >> 3);

    return Color((r5 << 11) | (g6 << 5) | b5);
  }

  constexpr uint16_t toRGB565() const { return value; }

private:
  uint16_t value;
};

// Colors
namespace Colors {
// Basic Colors
constexpr Color Black = Color(0x0000);
constexpr Color White = Color(0xFFFF);

// Colors
constexpr Color Red = Color(0xF800);
constexpr Color Green = Color(0x07E0);
constexpr Color Blue = Color(0x001F);

} // namespace Colors

} // namespace pico_hud
