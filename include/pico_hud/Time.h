#pragma once

#include <cstdint>

namespace pico_hud {

class Time {
public:
  /**
   * @brief Get current time in milliseconds since boot
   * @return Milliseconds since system start
   */
  static uint32_t millis();

  /**
   * @brief Get current time in microseconds since boot
   * @return Microseconds since system start
   */
  static uint64_t micros();

  /**
   * @brief Delay for specified milliseconds
   * @param ms Milliseconds to delay
   */
  static void delay_ms(uint32_t ms);

  /**
   * @brief Delay for specified microseconds
   * @param us Microseconds to delay
   */
  static void delay_us(uint32_t us);
};

} // namespace pico_hud

