#include "pico_hud/Time.h"
#include "pico/time.h"

namespace pico_hud {

uint32_t Time::millis() {
  return to_ms_since_boot(get_absolute_time());
}

uint64_t Time::micros() {
  return to_us_since_boot(get_absolute_time());
}

void Time::delay_ms(uint32_t ms) {
  sleep_ms(ms);
}

void Time::delay_us(uint32_t us) {
  sleep_us(us);
}

} // namespace pico_hud

