#pragma once

#include "pico_hud/IWidget.h"
#include "pico_hud/Color.h"

namespace pico_hud {

/**
 * @brief Crosshair/reticle widget for HUD
 */
class Crosshair : public IWidget {
public:
  Crosshair(int16_t center_x, int16_t center_y, uint16_t size, Color color = Colors::Green);
  
  void draw(IDisplay& display) override;

  void setSize(uint16_t size) { size_ = size; }
  void setColor(Color color) { color_ = color; }

private:
  uint16_t size_;
  Color color_;
};

} // namespace pico_hud

