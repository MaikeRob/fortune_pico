cmake_minimum_required(VERSION 3.21)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(test C CXX ASM)

pico_sdk_init()

add_executable(test
    src/main.c
    src/display.c
    src/joystick.c
    ../lib/pico-ssd1306/ssd1306.c
)

target_include_directories(test PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../lib/pico-ssd1306
    ${CMAKE_CURRENT_LIST_DIR}/headers
)

target_link_libraries(test
    pico_stdlib
    hardware_adc
    hardware_dma
    hardware_i2c
)

pico_add_extra_outputs(test)

pico_enable_stdio_usb(test 1)
