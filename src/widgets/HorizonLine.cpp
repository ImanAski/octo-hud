#include "pico_hud/widgets/HorizonLine.h"
#include "pico_hud/IDisplay.h"
#include "pico_hud/HUDManager.h"
#include <cmath>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace pico_hud {

HorizonLine::HorizonLine(int16_t x, int16_t y, uint16_t width, uint16_t height)
  : IWidget(x, y, width, height),
    pitch_(0.0f), roll_(0.0f),
    sky_color_(Colors::Blue),
    ground_color_(Color::fromRGB(139, 90, 43)), // Brown
    line_color_(Colors::White) {
}

void HorizonLine::update(HUDManager& hud) {
  // Get attitude sensor reading if available
  SensorReading pitch_reading = hud.getSensorReading("pitch");
  if (pitch_reading.is_valid) {
    pitch_ = pitch_reading.value;
  }
  
  SensorReading roll_reading = hud.getSensorReading("roll");
  if (roll_reading.is_valid) {
    roll_ = roll_reading.value;
  }
}

void HorizonLine::draw(IDisplay& display) {
  int16_t center_x = x_ + width_ / 2;
  int16_t center_y = y_ + height_ / 2;
  
  // Calculate horizon line position based on pitch
  // Pitch is in degrees, positive = nose up
  float pitch_pixels = (pitch_ / 90.0f) * (height_ / 2);
  int16_t horizon_y = center_y - static_cast<int16_t>(pitch_pixels);
  
  // Clamp horizon line to widget bounds
  horizon_y = std::max(y_, std::min(static_cast<int16_t>(y_ + height_), horizon_y));
  
  // Draw sky (above horizon)
  if (horizon_y > y_) {
    display.fillRect(x_, y_, width_, horizon_y - y_, sky_color_);
  }
  
  // Draw ground (below horizon)
  if (horizon_y < y_ + height_) {
    display.fillRect(x_, horizon_y, width_, (y_ + height_) - horizon_y, ground_color_);
  }
  
  // Draw horizon line
  display.drawLine(x_, horizon_y, x_ + width_, horizon_y, line_color_);
  
  // Draw pitch ladder
  drawPitchLadder(display, horizon_y);
  
  // Draw roll indicator (top center)
  int16_t roll_indicator_size = 20;
  int16_t roll_x = center_x;
  int16_t roll_y = y_ + 10;
  
  // Draw roll indicator line
  float roll_rad = roll_ * M_PI / 180.0f;
  int16_t roll_end_x = roll_x + static_cast<int16_t>(sin(roll_rad) * roll_indicator_size);
  int16_t roll_end_y = roll_y + static_cast<int16_t>(cos(roll_rad) * roll_indicator_size);
  display.drawLine(roll_x, roll_y, roll_end_x, roll_end_y, line_color_);
}

void HorizonLine::drawPitchLadder(IDisplay& display, int16_t horizon_y) {
  int16_t center_x = x_ + width_ / 2;
  
  // Draw pitch marks every 10 degrees
  for (int pitch = -90; pitch <= 90; pitch += 10) {
    if (pitch == 0) continue; // Skip horizon line itself
    
    float pitch_pixels = (pitch / 90.0f) * (height_ / 2);
    int16_t mark_y = horizon_y - static_cast<int16_t>(pitch_pixels);
    
    if (mark_y >= y_ && mark_y < y_ + height_) {
      // Draw horizontal line
      uint16_t line_width = (abs(pitch) % 30 == 0) ? 40 : 20;
      display.drawLine(center_x - line_width/2, mark_y, center_x + line_width/2, mark_y, line_color_);
      
      // Draw pitch value label (simplified - just show major marks)
      if (abs(pitch) % 30 == 0) {
        char label[8];
        snprintf(label, sizeof(label), "%d", abs(pitch));
        // Note: Would need font rendering here, simplified for now
      }
    }
  }
}

} // namespace pico_hud

