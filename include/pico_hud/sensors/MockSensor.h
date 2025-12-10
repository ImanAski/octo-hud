#pragma once

#include "pico_hud/ISensor.h"
#include "pico_hud/Time.h"
#include <string>
#include <random>

namespace pico_hud {

/**
 * @brief Mock sensor for testing
 * Generates simulated sensor readings
 */
class MockSensor : public ISensor {
public:
  MockSensor(const std::string& name, const std::string& unit, float min_value, float max_value, float initial_value = 0.0f);
  
  bool initialize() override;
  SensorReading read() override;
  std::string getName() override { return name_; }

  /**
   * @brief Set the current value
   */
  void setValue(float value);

  /**
   * @brief Enable/disable random variation
   */
  void setRandomVariation(bool enabled, float variation_amount = 0.1f);

private:
  std::string name_;
  std::string unit_;
  float min_value_;
  float max_value_;
  float current_value_;
  bool random_variation_;
  float variation_amount_;
  std::mt19937 rng_;
  std::uniform_real_distribution<float> dist_;
};

} // namespace pico_hud

