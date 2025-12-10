#include "pico_hud/sensors/MockSensor.h"

namespace pico_hud {

MockSensor::MockSensor(const std::string& name, const std::string& unit, 
                       float min_value, float max_value, float initial_value)
  : name_(name), unit_(unit), min_value_(min_value), max_value_(max_value),
    current_value_(initial_value), random_variation_(false), variation_amount_(0.1f),
    rng_(42), dist_(-1.0f, 1.0f) {
}

bool MockSensor::initialize() {
  return true;
}

SensorReading MockSensor::read() {
  SensorReading reading;
  reading.unit = unit_;
  reading.is_valid = true;
  reading.timestamp = Time::millis();
  
  if (random_variation_) {
    float variation = dist_(rng_) * variation_amount_;
    reading.value = std::max(min_value_, std::min(max_value_, current_value_ + variation));
  } else {
    reading.value = current_value_;
  }
  
  return reading;
}

void MockSensor::setValue(float value) {
  current_value_ = std::max(min_value_, std::min(max_value_, value));
}

void MockSensor::setRandomVariation(bool enabled, float variation_amount) {
  random_variation_ = enabled;
  variation_amount_ = variation_amount;
}

} // namespace pico_hud

