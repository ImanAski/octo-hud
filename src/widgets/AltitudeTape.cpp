#include "pico_hud/widgets/AltitudeTape.h"
#include "pico_hud/IDisplay.h"
#include "pico_hud/HUDManager.h"
#include "pico_hud/Font.h"
#include <cmath>
#include <algorithm>
#include <cstdio>

namespace pico_hud {

AltitudeTape::AltitudeTape(int16_t x, int16_t y, uint16_t width, uint16_t height)
  : IWidget(x, y, width, height),
    altitude_(0.0f), min_altitude_(0.0f), max_altitude_(50000.0f),
    background_color_(Colors::Black),
    text_color_(Colors::Green),
    line_color_(Colors::Green) {
}

void AltitudeTape::update(HUDManager& hud) {
  SensorReading reading = hud.getSensorReading("altitude");
  if (reading.is_valid) {
    altitude_ = reading.value;
  }
}

void AltitudeTape::draw(IDisplay& display) {
  // Draw background
  display.fillRect(x_, y_, width_, height_, background_color_);
  
  // Draw border
  display.drawRect(x_, y_, width_, height_, line_color_);
  
  int16_t center_y = y_ + height_ / 2;
  
  // Calculate which altitudes to display
  float altitude_range = max_altitude_ - min_altitude_;
  float pixels_per_foot = static_cast<float>(height_) / altitude_range;
  
  // Draw altitude marks
  float start_alt = altitude_ - (center_y - y_) / pixels_per_foot;
  float end_alt = altitude_ + (y_ + height_ - center_y) / pixels_per_foot;
  
  // Round to nearest 100
  int start_mark = static_cast<int>((start_alt / 100.0f) - 1) * 100;
  int end_mark = static_cast<int>((end_alt / 100.0f) + 1) * 100;
  
  for (int mark_alt = start_mark; mark_alt <= end_mark; mark_alt += 100) {
    if (mark_alt < min_altitude_ || mark_alt > max_altitude_) continue;
    
    float offset = (mark_alt - altitude_) * pixels_per_foot;
    int16_t mark_y = center_y - static_cast<int16_t>(offset);
    
    if (mark_y >= y_ && mark_y < y_ + height_) {
      drawAltitudeMark(display, mark_alt, mark_y);
    }
  }
  
  // Draw center indicator (current altitude)
  display.drawLine(x_, center_y, x_ + width_, center_y, Colors::White);
  
  // Draw current altitude value
  char alt_str[16];
  snprintf(alt_str, sizeof(alt_str), "%.0f", altitude_);
  display.drawText(x_ + 2, center_y - 4, alt_str, font_8x8, text_color_, background_color_);
}

void AltitudeTape::drawAltitudeMark(IDisplay& display, float alt_value, int16_t y_pos) {
  // Draw tick mark
  uint16_t tick_width = (static_cast<int>(alt_value) % 500 == 0) ? width_ - 4 : width_ / 2;
  display.drawLine(x_, y_pos, x_ + tick_width, y_pos, line_color_);
  
  // Draw altitude value for major marks
  if (static_cast<int>(alt_value) % 500 == 0) {
    char label[8];
    snprintf(label, sizeof(label), "%.0f", alt_value / 1000.0f); // Show in thousands
    display.drawText(x_ + 2, y_pos - 4, label, font_8x8, text_color_, background_color_);
  }
}

} // namespace pico_hud

