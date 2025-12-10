#pragma once

#include "pico_hud/IWidget.h"
#include "pico_hud/Color.h"
#include <string>

namespace pico_hud {

/**
 * @brief Simple data display widget
 * Shows sensor reading as text
 */
class DataDisplay : public IWidget {
public:
  DataDisplay(int16_t x, int16_t y, const std::string& label, const std::string& sensor_name);
  
  void update(HUDManager& hud) override;
  void draw(IDisplay& display) override;

  void setLabel(const std::string& label) { label_ = label; }
  void setPrecision(int precision) { precision_ = precision; }
  void setColor(Color color) { color_ = color; }

private:
  std::string label_;
  std::string sensor_name_;
  float current_value_;
  std::string unit_;
  int precision_;
  Color color_;
  Color background_color_;
};

} // namespace pico_hud

