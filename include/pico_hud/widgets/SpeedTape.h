#pragma once

#include "pico_hud/IWidget.h"
#include "pico_hud/Color.h"

namespace pico_hud {

/**
 * @brief Vertical speed tape widget
 * Shows airspeed with vertical scrolling tape
 */
class SpeedTape : public IWidget {
public:
  SpeedTape(int16_t x, int16_t y, uint16_t width, uint16_t height);
  
  void update(HUDManager& hud) override;
  void draw(IDisplay& display) override;

  void setSpeed(float speed_knots) { speed_ = speed_knots; }
  void setMinSpeed(float min) { min_speed_ = min; }
  void setMaxSpeed(float max) { max_speed_ = max; }

private:
  float speed_;
  float min_speed_;
  float max_speed_;
  Color background_color_;
  Color text_color_;
  Color line_color_;
  
  void drawSpeedMark(IDisplay& display, float speed_value, int16_t y_pos);
};

} // namespace pico_hud

