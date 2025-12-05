#pragma once

#include <cstdint>
#include <string>
namespace pico_hud {

struct SensorReading {
  float value;
  std::string unit;
  bool is_valid;
  uint32_t timestamp;
};

class ISensor {
  virtual ~ISensor() = default;

  /*
   * @brief Initialize the sensor
   * @return bool
   */
  virtual bool initialize() = 0;

  /*
   * @brief Reads the current value of sensor.
   * @returns SensorReading
   */
  virtual SensorReading read() = 0;

  /*
   * @brief Returns the name of the registered sensor.
   */
  virtual std::string getName() = 0;
};
} // namespace pico_hud
