#include "pico_hud/display/VirtualDisplay.h"
#include "pico_hud/Font.h"
#include <algorithm>
#include <cmath>

namespace pico_hud {

VirtualDisplay::VirtualDisplay(uint16_t width, uint16_t height)
  : width_(width), height_(height), framebuffer_(width * height, 0) {
}

VirtualDisplay::~VirtualDisplay() {
}

bool VirtualDisplay::initialize() {
  clear();
  return true;
}

void VirtualDisplay::clear(Color color) {
  uint16_t color565 = color.toRGB565();
  std::fill(framebuffer_.begin(), framebuffer_.end(), color565);
}

void VirtualDisplay::drawPixel(int16_t x, int16_t y, Color color) {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return;
  }
  framebuffer_[y * width_ + x] = color.toRGB565();
}

void VirtualDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, Color color) {
  // Bresenham's line algorithm
  int16_t dx = abs(x1 - x0);
  int16_t dy = abs(y1 - y0);
  int16_t sx = (x0 < x1) ? 1 : -1;
  int16_t sy = (y0 < y1) ? 1 : -1;
  int16_t err = dx - dy;

  uint16_t color565 = color.toRGB565();

  while (true) {
    drawPixel(x0, y0, color);

    if (x0 == x1 && y0 == y1) break;

    int16_t e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void VirtualDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color) {
  drawLine(x, y, x + w - 1, y, color);
  drawLine(x + w - 1, y, x + w - 1, y + h - 1, color);
  drawLine(x + w - 1, y + h - 1, x, y + h - 1, color);
  drawLine(x, y + h - 1, x, y, color);
}

void VirtualDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, Color color) {
  uint16_t color565 = color.toRGB565();
  
  // Clamp to display bounds
  int16_t x0 = std::max(0, x);
  int16_t y0 = std::max(0, y);
  int16_t x1 = std::min(static_cast<int16_t>(width_), static_cast<int16_t>(x + w));
  int16_t y1 = std::min(static_cast<int16_t>(height_), static_cast<int16_t>(y + h));

  for (int16_t py = y0; py < y1; py++) {
    for (int16_t px = x0; px < x1; px++) {
      framebuffer_[py * width_ + px] = color565;
    }
  }
}

void VirtualDisplay::drawText(int16_t x, int16_t y, const char *text, Color color, Color bgColor) {
  drawText(x, y, text, font_8x8, color, bgColor);
}

void VirtualDisplay::drawText(int16_t x, int16_t y, const char *text, const Font& font, Color color, Color bgColor) {
  int16_t cx = x;
  const char* p = text;
  
  while (*p) {
    const Glyph* glyph = FontRenderer::getGlyph(font, *p);
    if (glyph) {
      drawGlyph(cx + glyph->x_offset, y + glyph->y_offset, *glyph, color, bgColor);
      cx += glyph->x_advance;
    }
    p++;
  }
}

void VirtualDisplay::drawGlyph(int16_t x, int16_t y, const Glyph& glyph, Color color, Color bgColor) {
  uint16_t fg565 = color.toRGB565();
  uint16_t bg565 = bgColor.toRGB565();
  
  const uint8_t* bitmap = glyph.bitmap;
  
  for (uint8_t row = 0; row < glyph.height; row++) {
    uint8_t byte = bitmap[row];
    for (uint8_t col = 0; col < glyph.width; col++) {
      if (byte & (1 << (7 - col))) {
        drawPixel(x + col, y + row, color);
      } else if (bgColor.toRGB565() != Colors::Black.toRGB565()) {
        drawPixel(x + col, y + row, bgColor);
      }
    }
  }
}

void VirtualDisplay::flush() {
  // Nothing to do for virtual display
}

Color VirtualDisplay::getPixel(int16_t x, int16_t y) const {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return Colors::Black;
  }
  return Color(framebuffer_[y * width_ + x]);
}

} // namespace pico_hud

