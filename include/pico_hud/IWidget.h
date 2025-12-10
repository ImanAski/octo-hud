#pragma once

#include "Color.h"
#include <cstdint>

namespace pico_hud {

class IDisplay;
class HUDManager;

class IWidget {
public:
  IWidget(int16_t x, int16_t y, uint16_t width, uint16_t height)
    : x_(x), y_(y), width_(width), height_(height), visible_(true), id_(next_id_++) {}
  
  virtual ~IWidget() = default;

  // Position and size
  int16_t getX() const { return x_; }
  int16_t getY() const { return y_; }
  uint16_t getWidth() const { return width_; }
  uint16_t getHeight() const { return height_; }
  void setPosition(int16_t x, int16_t y) { x_ = x; y_ = y; }
  void setSize(uint16_t width, uint16_t height) { width_ = width; height_ = height; }

  // Visibility
  bool isVisible() const { return visible_; }
  void setVisible(bool visible) { visible_ = visible; }

  // ID
  uint32_t getId() const { return id_; }

  // Update and draw
  virtual void update(HUDManager& hud) {}
  virtual void draw(IDisplay& display) = 0;

protected:
  int16_t x_;
  int16_t y_;
  uint16_t width_;
  uint16_t height_;
  bool visible_;

private:
  uint32_t id_;
  static uint32_t next_id_;
};

} // namespace pico_hud

