include_directories(
    ../include
)

add_executable(drawtest
    src/drawtest.c
)
target_link_libraries(drawtest 
    microgl
)
pico_enable_stdio_usb(drawtest 1)
pico_enable_stdio_uart(drawtest 0)
pico_add_extra_outputs(drawtest)

add_executable(hellomicrogl
    src/hellomicrogl.c
)
target_link_libraries(hellomicrogl 
    microgl
)
pico_enable_stdio_usb(hellomicrogl 1)
pico_enable_stdio_uart(hellomicrogl 0)
pico_add_extra_outputs(hellomicrogl)