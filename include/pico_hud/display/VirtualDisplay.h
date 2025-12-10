#pragma once

#include "pico_hud/IDisplay.h"
#include <vector>
#include <cstring>

namespace pico_hud {

/**
 * @brief Virtual display for testing/simulation
 * Stores pixel data in memory
 */
class VirtualDisplay : public IDisplay {
public:
  VirtualDisplay(uint16_t width, uint16_t height);
  virtual ~VirtualDisplay();

  bool initialize() override;

  uint16_t getWidth() const override { return width_; }
  uint16_t getHeight() const override { return height_; }

  void clear(Color color = Colors::Black) override;
  void drawPixel(int16_t x, int16_t y, Color color) override;
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Color color) override;
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color) override;
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color) override;
  void drawText(int16_t x, int16_t y, const char *text, Color color, Color bgColor) override;
  void drawText(int16_t x, int16_t y, const char *text, const Font& font, Color color, Color bgColor = Colors::Black) override;
  void flush() override;

  /**
   * @brief Get pixel color at position
   */
  Color getPixel(int16_t x, int16_t y) const;

  /**
   * @brief Get raw framebuffer
   */
  const uint16_t* getFramebuffer() const { return framebuffer_.data(); }

private:
  uint16_t width_;
  uint16_t height_;
  std::vector<uint16_t> framebuffer_;

  void drawGlyph(int16_t x, int16_t y, const Glyph& glyph, Color color, Color bgColor);
};

} // namespace pico_hud

