cmake_minimum_required(VERSION 3.21)

set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
include(${PICO_SDK_PATH}/pico_sdk_init.cmake)

project(Hud VERSION 1.0 LANGUAGES C CXX)

# init for pico sdk
pico_sdk_init()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Library sources
set(HUD_LIB_SOURCES
  src/Time.cpp
  src/Font.cpp
  src/IDisplay.cpp
  src/IWidget.cpp
  src/HUDManager.cpp
  src/display/VirtualDisplay.cpp
  src/sensors/MockSensor.cpp
  src/widgets/Crosshair.cpp
  src/widgets/HorizonLine.cpp
  src/widgets/SpeedTape.cpp
  src/widgets/AltitudeTape.cpp
  src/widgets/DataDisplay.cpp
)

# Create library
add_library(pico_hud STATIC ${HUD_LIB_SOURCES})

# Link pico SDK
target_link_libraries(pico_hud pico_stdlib pico_time)

# Executable
add_executable(hud_main src/main.cpp)
target_link_libraries(hud_main pico_hud pico_stdlib pico_time)

# Enable USB output, disable UART output
pico_enable_stdio_usb(hud_main 1)
pico_enable_stdio_uart(hud_main 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(hud_main)
