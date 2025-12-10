#pragma once

#include "pico_hud/IWidget.h"
#include "pico_hud/Color.h"

namespace pico_hud {

/**
 * @brief Vertical altitude tape widget
 * Shows altitude with vertical scrolling tape
 */
class AltitudeTape : public IWidget {
public:
  AltitudeTape(int16_t x, int16_t y, uint16_t width, uint16_t height);
  
  void update(HUDManager& hud) override;
  void draw(IDisplay& display) override;

  void setAltitude(float altitude_feet) { altitude_ = altitude_feet; }
  void setMinAltitude(float min) { min_altitude_ = min; }
  void setMaxAltitude(float max) { max_altitude_ = max; }

private:
  float altitude_;
  float min_altitude_;
  float max_altitude_;
  Color background_color_;
  Color text_color_;
  Color line_color_;
  
  void drawAltitudeMark(IDisplay& display, float alt_value, int16_t y_pos);
};

} // namespace pico_hud

