#include "pico_hud/HUDManager.h"
#include "pico_hud/IWidget.h"
#include "pico_hud/Time.h"

namespace pico_hud {

HUDManager::HUDManager() : initialized_(false) {
}

HUDManager::~HUDManager() {
}

bool HUDManager::initialize(std::unique_ptr<IDisplay> display) {
  if (!display) {
    return false;
  }
  
  display_ = std::move(display);
  
  if (!display_->initialize()) {
    return false;
  }
  
  initialized_ = true;
  return true;
}

bool HUDManager::registerSensor(const std::string& name, std::unique_ptr<ISensor> sensor) {
  if (!sensor) {
    return false;
  }
  
  if (!sensor->initialize()) {
    return false;
  }
  
  sensors_[name] = std::move(sensor);
  return true;
}

SensorReading HUDManager::getSensorReading(const std::string& name) {
  auto it = sensors_.find(name);
  if (it != sensors_.end()) {
    return it->second->read();
  }
  
  // Return invalid reading
  SensorReading invalid;
  invalid.is_valid = false;
  invalid.value = 0.0f;
  invalid.unit = "";
  invalid.timestamp = Time::millis();
  return invalid;
}

void HUDManager::addWidget(std::unique_ptr<IWidget> widget) {
  if (widget) {
    widgets_.push_back(std::move(widget));
  }
}

void HUDManager::removeWidget(uint32_t widget_id) {
  widgets_.erase(
    std::remove_if(widgets_.begin(), widgets_.end(),
      [widget_id](const std::unique_ptr<IWidget>& w) {
        return w->getId() == widget_id;
      }),
    widgets_.end()
  );
}

void HUDManager::update() {
  if (!initialized_) {
    return;
  }
  
  // Update scheduler
  scheduler_.run();
  
  // Update all widgets
  for (auto& widget : widgets_) {
    if (widget->isVisible()) {
      widget->update(*this);
    }
  }
}

void HUDManager::render() {
  if (!initialized_ || !display_) {
    return;
  }
  
  // Clear display
  display_->clear(Colors::Black);
  
  // Render all widgets
  for (auto& widget : widgets_) {
    if (widget->isVisible()) {
      widget->draw(*display_);
    }
  }
  
  // Flush to display
  display_->flush();
}

} // namespace pico_hud

