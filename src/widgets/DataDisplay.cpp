#include "pico_hud/widgets/DataDisplay.h"
#include "pico_hud/IDisplay.h"
#include "pico_hud/HUDManager.h"
#include "pico_hud/Font.h"
#include <cstdio>

namespace pico_hud {

DataDisplay::DataDisplay(int16_t x, int16_t y, const std::string& label, const std::string& sensor_name)
  : IWidget(x, y, 100, 20),
    label_(label), sensor_name_(sensor_name),
    current_value_(0.0f), unit_(""), precision_(1),
    color_(Colors::Green), background_color_(Colors::Black) {
}

void DataDisplay::update(HUDManager& hud) {
  SensorReading reading = hud.getSensorReading(sensor_name_);
  if (reading.is_valid) {
    current_value_ = reading.value;
    unit_ = reading.unit;
  }
}

void DataDisplay::draw(IDisplay& display) {
  // Draw background
  display.fillRect(x_, y_, width_, height_, background_color_);
  
  // Draw label
  display.drawText(x_ + 2, y_ + 2, label_.c_str(), font_8x8, color_, background_color_);
  
  // Draw value
  char value_str[32];
  if (precision_ == 0) {
    snprintf(value_str, sizeof(value_str), "%.0f %s", current_value_, unit_.c_str());
  } else if (precision_ == 1) {
    snprintf(value_str, sizeof(value_str), "%.1f %s", current_value_, unit_.c_str());
  } else {
    snprintf(value_str, sizeof(value_str), "%.2f %s", current_value_, unit_.c_str());
  }
  
  display.drawText(x_ + 2, y_ + 12, value_str, font_8x8, color_, background_color_);
}

} // namespace pico_hud

