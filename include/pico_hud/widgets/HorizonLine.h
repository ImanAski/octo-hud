#pragma once

#include "pico_hud/IWidget.h"
#include "pico_hud/Color.h"

namespace pico_hud {

/**
 * @brief Artificial horizon line widget
 * Shows pitch angle with horizon line
 */
class HorizonLine : public IWidget {
public:
  HorizonLine(int16_t x, int16_t y, uint16_t width, uint16_t height);
  
  void update(HUDManager& hud) override;
  void draw(IDisplay& display) override;

  void setPitch(float pitch_degrees) { pitch_ = pitch_degrees; }
  void setRoll(float roll_degrees) { roll_ = roll_degrees; }

private:
  float pitch_;  // Pitch angle in degrees
  float roll_;   // Roll angle in degrees
  Color sky_color_;
  Color ground_color_;
  Color line_color_;
  
  void drawPitchLadder(IDisplay& display, int16_t center_y);
};

} // namespace pico_hud

