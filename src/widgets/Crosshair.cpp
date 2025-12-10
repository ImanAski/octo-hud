#include "pico_hud/widgets/Crosshair.h"
#include "pico_hud/IDisplay.h"

namespace pico_hud {

Crosshair::Crosshair(int16_t center_x, int16_t center_y, uint16_t size, Color color)
  : IWidget(center_x - size/2, center_y - size/2, size, size),
    size_(size), color_(color) {
}

void Crosshair::draw(IDisplay& display) {
  int16_t cx = x_ + width_ / 2;
  int16_t cy = y_ + height_ / 2;
  
  // Horizontal line
  display.drawLine(cx - size_/2, cy, cx + size_/2, cy, color_);
  
  // Vertical line
  display.drawLine(cx, cy - size_/2, cx, cy + size_/2, color_);
  
  // Center dot
  display.fillRect(cx - 2, cy - 2, 5, 5, color_);
}

} // namespace pico_hud

