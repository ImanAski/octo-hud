#pragma once

#include <cstdint>
#include <cstddef>

namespace pico_hud {

struct Glyph {
  uint8_t width;
  uint8_t height;
  uint8_t x_offset;
  uint8_t y_offset;
  uint8_t x_advance;
  const uint8_t* bitmap;
};

struct Font {
  uint8_t height;
  uint8_t baseline;
  const Glyph* glyphs;
  size_t glyph_count;
  uint8_t first_char;
  uint8_t last_char;
};

class FontRenderer {
public:
  /**
   * @brief Get glyph for a character
   * @param font Font to use
   * @param c Character to get glyph for
   * @return Pointer to glyph or nullptr if not found
   */
  static const Glyph* getGlyph(const Font& font, char c);

  /**
   * @brief Measure text width
   * @param font Font to use
   * @param text Text to measure
   * @return Width in pixels
   */
  static uint16_t measureText(const Font& font, const char* text);
};

// Built-in 8x8 monospace font
extern const Font font_8x8;

} // namespace pico_hud

