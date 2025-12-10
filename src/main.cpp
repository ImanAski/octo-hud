#include "pico_hud/HUDManager.h"
#include "pico_hud/display/VirtualDisplay.h"
#include "pico_hud/sensors/MockSensor.h"
#include "pico_hud/widgets/Crosshair.h"
#include "pico_hud/widgets/HorizonLine.h"
#include "pico_hud/widgets/SpeedTape.h"
#include "pico_hud/widgets/AltitudeTape.h"
#include "pico_hud/widgets/DataDisplay.h"
#include "pico_hud/Time.h"
#include "pico/stdlib.h"
#include <memory>
#include <cmath>

int main() {
  // Initialize stdio for UART output
  stdio_init_all();

  // Create HUD manager
  pico_hud::HUDManager hud;

  // Create virtual display (320x240 for demo)
  auto display = std::make_unique<pico_hud::VirtualDisplay>(320, 240);
  
  if (!hud.initialize(std::move(display))) {
    // Error initializing
    return 1;
  }

  // Register mock sensors
  auto speed_sensor = std::make_unique<pico_hud::MockSensor>(
    "speed", "kts", 0.0f, 500.0f, 250.0f
  );
  speed_sensor->setRandomVariation(true, 5.0f);
  hud.registerSensor("speed", std::move(speed_sensor));

  auto altitude_sensor = std::make_unique<pico_hud::MockSensor>(
    "altitude", "ft", 0.0f, 50000.0f, 10000.0f
  );
  altitude_sensor->setRandomVariation(true, 50.0f);
  hud.registerSensor("altitude", std::move(altitude_sensor));

  auto pitch_sensor = std::make_unique<pico_hud::MockSensor>(
    "pitch", "deg", -90.0f, 90.0f, 0.0f
  );
  pitch_sensor->setRandomVariation(true, 2.0f);
  hud.registerSensor("pitch", std::move(pitch_sensor));

  auto roll_sensor = std::make_unique<pico_hud::MockSensor>(
    "roll", "deg", -180.0f, 180.0f, 0.0f
  );
  roll_sensor->setRandomVariation(true, 1.0f);
  hud.registerSensor("roll", std::move(roll_sensor));

  // Add HUD widgets
  // Crosshair in center
  hud.addWidget(std::make_unique<pico_hud::Crosshair>(160, 120, 40, pico_hud::Colors::Green));

  // Horizon line (full width, centered vertically)
  hud.addWidget(std::make_unique<pico_hud::HorizonLine>(0, 40, 320, 160));

  // Speed tape on left
  hud.addWidget(std::make_unique<pico_hud::SpeedTape>(10, 20, 50, 200));

  // Altitude tape on right
  hud.addWidget(std::make_unique<pico_hud::AltitudeTape>(260, 20, 50, 200));

  // Data displays
  hud.addWidget(std::make_unique<pico_hud::DataDisplay>(10, 5, "SPD", "speed"));
  hud.addWidget(std::make_unique<pico_hud::DataDisplay>(100, 5, "ALT", "altitude"));

  // Main loop
  uint32_t last_render_ms = 0;
  const uint32_t render_interval_ms = 50; // 20 FPS

  while (true) {
    uint32_t current_ms = pico_hud::Time::millis();

    // Update HUD (sensors, widgets)
    hud.update();

    // Render at fixed interval
    if (current_ms - last_render_ms >= render_interval_ms) {
      hud.render();
      last_render_ms = current_ms;
    }

    // Small delay to prevent tight loop
    pico_hud::Time::delay_ms(10);
  }

  return 0;
}

