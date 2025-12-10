#pragma once

#include "IDisplay.h"
#include "ISensor.h"
#include "Scheduler.h"
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

namespace pico_hud {

class IWidget;

class HUDManager {
public:
  HUDManager();
  ~HUDManager();

  /**
   * @brief Initialize the HUD system
   * @param display Display instance to use
   * @return true if successful
   */
  bool initialize(std::unique_ptr<IDisplay> display);

  /**
   * @brief Register a sensor with the HUD
   * @param name Sensor name/identifier
   * @param sensor Sensor instance
   * @return true if successful
   */
  bool registerSensor(const std::string& name, std::unique_ptr<ISensor> sensor);

  /**
   * @brief Get sensor reading by name
   * @param name Sensor name
   * @return SensorReading or invalid reading if not found
   */
  SensorReading getSensorReading(const std::string& name);

  /**
   * @brief Add a widget to the HUD
   * @param widget Widget instance
   */
  void addWidget(std::unique_ptr<IWidget> widget);

  /**
   * @brief Remove a widget from the HUD
   * @param widget_id Widget identifier
   */
  void removeWidget(uint32_t widget_id);

  /**
   * @brief Get display instance
   * @return Pointer to display or nullptr
   */
  IDisplay* getDisplay() { return display_.get(); }

  /**
   * @brief Update the HUD (call in main loop)
   */
  void update();

  /**
   * @brief Render the HUD (call in main loop)
   */
  void render();

  /**
   * @brief Get the scheduler instance
   * @return Reference to scheduler
   */
  Scheduler& getScheduler() { return scheduler_; }

private:
  std::unique_ptr<IDisplay> display_;
  std::unordered_map<std::string, std::unique_ptr<ISensor>> sensors_;
  std::vector<std::unique_ptr<IWidget>> widgets_;
  Scheduler scheduler_;
  bool initialized_;
};

} // namespace pico_hud

