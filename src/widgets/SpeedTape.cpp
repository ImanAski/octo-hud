#include "pico_hud/widgets/SpeedTape.h"
#include "pico_hud/IDisplay.h"
#include "pico_hud/HUDManager.h"
#include "pico_hud/Font.h"
#include <cmath>
#include <algorithm>
#include <cstdio>

namespace pico_hud {

SpeedTape::SpeedTape(int16_t x, int16_t y, uint16_t width, uint16_t height)
  : IWidget(x, y, width, height),
    speed_(0.0f), min_speed_(0.0f), max_speed_(500.0f),
    background_color_(Colors::Black),
    text_color_(Colors::Green),
    line_color_(Colors::Green) {
}

void SpeedTape::update(HUDManager& hud) {
  SensorReading reading = hud.getSensorReading("speed");
  if (reading.is_valid) {
    speed_ = reading.value;
  }
}

void SpeedTape::draw(IDisplay& display) {
  // Draw background
  display.fillRect(x_, y_, width_, height_, background_color_);
  
  // Draw border
  display.drawRect(x_, y_, width_, height_, line_color_);
  
  int16_t center_y = y_ + height_ / 2;
  
  // Calculate which speeds to display
  float speed_range = max_speed_ - min_speed_;
  float pixels_per_knot = static_cast<float>(height_) / speed_range;
  
  // Draw speed marks
  float start_speed = speed_ - (center_y - y_) / pixels_per_knot;
  float end_speed = speed_ + (y_ + height_ - center_y) / pixels_per_knot;
  
  // Round to nearest 10
  int start_mark = static_cast<int>((start_speed / 10.0f) - 1) * 10;
  int end_mark = static_cast<int>((end_speed / 10.0f) + 1) * 10;
  
  for (int mark_speed = start_mark; mark_speed <= end_mark; mark_speed += 10) {
    if (mark_speed < min_speed_ || mark_speed > max_speed_) continue;
    
    float offset = (mark_speed - speed_) * pixels_per_knot;
    int16_t mark_y = center_y - static_cast<int16_t>(offset);
    
    if (mark_y >= y_ && mark_y < y_ + height_) {
      drawSpeedMark(display, mark_speed, mark_y);
    }
  }
  
  // Draw center indicator (current speed)
  display.drawLine(x_, center_y, x_ + width_, center_y, Colors::White);
  
  // Draw current speed value
  char speed_str[16];
  snprintf(speed_str, sizeof(speed_str), "%.0f", speed_);
  display.drawText(x_ + 2, center_y - 4, speed_str, font_8x8, text_color_, background_color_);
}

void SpeedTape::drawSpeedMark(IDisplay& display, float speed_value, int16_t y_pos) {
  // Draw tick mark
  uint16_t tick_width = (static_cast<int>(speed_value) % 50 == 0) ? width_ - 4 : width_ / 2;
  display.drawLine(x_ + width_ - tick_width, y_pos, x_ + width_, y_pos, line_color_);
  
  // Draw speed value for major marks
  if (static_cast<int>(speed_value) % 50 == 0) {
    char label[8];
    snprintf(label, sizeof(label), "%.0f", speed_value);
    display.drawText(x_ + 2, y_pos - 4, label, font_8x8, text_color_, background_color_);
  }
}

} // namespace pico_hud

