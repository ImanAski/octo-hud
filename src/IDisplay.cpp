#include "pico_hud/IDisplay.h"

namespace pico_hud {

IDisplay::~IDisplay() = default;

bool IDisplay::initialize() {
  return true;
}

} // namespace pico_hud

