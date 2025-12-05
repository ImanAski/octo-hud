#pragma once
#include "Color.h"
#include <cstdint>

namespace pico_hud {
class IDisplay {
public:
  virtual ~IDisplay();

  virtual bool initialize();

  // Display Information
  virtual uint16_t getWidth() const = 0;
  virtual uint16_t getHeight() const = 0;

  // Utils
  virtual void clear(Color color = Colors::Black) = 0;
  virtual void drawPixel(int16_t x, int16_t y, Color color) = 0;
  virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
                        Color color) = 0;
  virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        Color color) = 0;
  virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,
                        Color color) = 0;

  // Text Renderring
  virtual void drawText(int16_t x, int16_t y, const char *text, Color color,
                        Color bgColor) = 0;

  virtual void flush() = 0;
};
} // namespace pico_hud
