# Pico HUD - Fighter Jet HUD System

A comprehensive Heads-Up Display (HUD) library for optical systems, designed for fighter jet demonstrations. Built for the Raspberry Pi Pico (RP2040) using the Pico SDK.

## Features

- **Modular Architecture**: Clean interface-based design for displays, sensors, and widgets
- **Real-time Rendering**: Efficient update and render pipeline
- **Fighter Jet HUD Elements**:
  - Artificial Horizon Line with pitch ladder
  - Speed Tape (vertical airspeed indicator)
  - Altitude Tape (vertical altitude indicator)
  - Crosshair/Reticle
  - Data Displays (sensor readouts)
- **Sensor Integration**: Flexible sensor interface with mock sensors for testing
- **Font Rendering**: Built-in bitmap font system
- **Task Scheduler**: Time-based task scheduling system

## Project Structure

```
pico_hud/
├── core/
│   ├── HUDManager.h/cpp    # Main HUD controller
│   ├── Time.h/cpp          # Time utilities
│   └── Font.h/cpp          # Font rendering system
├── display/
│   └── implementations/
│       └── VirtualDisplay.h/cpp  # Virtual display for testing
├── sensors/
│   └── implementations/
│       └── MockSensor.h/cpp       # Mock sensor for testing
├── widgets/
│   ├── IWidget.h/cpp              # Base widget interface
│   ├── Crosshair.h/cpp           # Crosshair widget
│   ├── HorizonLine.h/cpp         # Artificial horizon
│   ├── SpeedTape.h/cpp           # Speed tape
│   ├── AltitudeTape.h/cpp        # Altitude tape
│   └── DataDisplay.h/cpp         # Data display widget
└── main.cpp                      # Example application
```

## Building

### Prerequisites

- Raspberry Pi Pico SDK installed
- CMake 3.21 or later
- ARM GCC toolchain

### Build Steps

1. Set the PICO_SDK_PATH environment variable:
   ```bash
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```

2. Create build directory:
   ```bash
   mkdir build
   cd build
   ```

3. Configure and build:
   ```bash
   cmake ..
   make
   ```

4. The output files will be in `build/`:
   - `hud_main.uf2` - For flashing to Pico
   - `hud_main.elf` - ELF binary
   - `hud_main.bin` - Binary file

## Usage

### Basic Example

```cpp
#include "pico_hud/HUDManager.h"
#include "pico_hud/display/VirtualDisplay.h"
#include "pico_hud/sensors/MockSensor.h"
#include "pico_hud/widgets/Crosshair.h"

int main() {
  pico_hud::HUDManager hud;
  
  // Create and initialize display
  auto display = std::make_unique<pico_hud::VirtualDisplay>(320, 240);
  hud.initialize(std::move(display));
  
  // Register sensors
  auto speed_sensor = std::make_unique<pico_hud::MockSensor>(
    "speed", "kts", 0.0f, 500.0f, 250.0f
  );
  hud.registerSensor("speed", std::move(speed_sensor));
  
  // Add widgets
  hud.addWidget(std::make_unique<pico_hud::Crosshair>(160, 120, 40));
  
  // Main loop
  while (true) {
    hud.update();
    hud.render();
    pico_hud::Time::delay_ms(50);
  }
  
  return 0;
}
```

### Creating Custom Sensors

Implement the `ISensor` interface:

```cpp
class MySensor : public pico_hud::ISensor {
public:
  bool initialize() override { /* ... */ }
  SensorReading read() override { /* ... */ }
  std::string getName() override { return "my_sensor"; }
};
```

### Creating Custom Widgets

Extend the `IWidget` class:

```cpp
class MyWidget : public pico_hud::IWidget {
public:
  MyWidget(int16_t x, int16_t y) 
    : IWidget(x, y, 100, 50) {}
  
  void update(HUDManager& hud) override { /* ... */ }
  void draw(IDisplay& display) override { /* ... */ }
};
```

### Creating Custom Displays

Implement the `IDisplay` interface:

```cpp
class MyDisplay : public pico_hud::IDisplay {
public:
  uint16_t getWidth() const override { return 320; }
  uint16_t getHeight() const override { return 240; }
  void clear(Color color) override { /* ... */ }
  void drawPixel(int16_t x, int16_t y, Color color) override { /* ... */ }
  // ... implement other methods
};
```

## Widgets

### Crosshair
Simple crosshair/reticle for targeting.

### HorizonLine
Artificial horizon with:
- Pitch angle display
- Roll indicator
- Pitch ladder marks
- Sky/ground separation

### SpeedTape
Vertical scrolling speed tape showing:
- Current airspeed
- Speed marks (every 10 knots)
- Major marks (every 50 knots)

### AltitudeTape
Vertical scrolling altitude tape showing:
- Current altitude
- Altitude marks (every 100 feet)
- Major marks (every 500 feet)

### DataDisplay
Simple text display for sensor values with label and unit.

## Sensors

### MockSensor
Simulated sensor for testing:
- Configurable value range
- Random variation support
- Manual value setting

## Future Enhancements

- [ ] Hardware display drivers (ST7789, SSD1306)
- [ ] Real sensor implementations (IMU, barometer, etc.)
- [ ] Heading indicator widget
- [ ] Warning/alert system
- [ ] Configuration system
- [ ] Performance optimizations (DMA, double buffering)
- [ ] 3D coordinate transformations
- [ ] Sensor fusion algorithms

## License

No License. Use it anyhow you like.

## Contributing

There are still no known contribution guideline as this project is for a university demonstration.
