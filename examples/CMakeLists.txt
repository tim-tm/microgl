add_executable(microgl_examples
    src/init.c
)

target_link_libraries(microgl_examples 
    microgl
)

include_directories(
    ../include
)

pico_enable_stdio_usb(microgl_examples 1)
pico_enable_stdio_uart(microgl_examples 0)

pico_add_extra_outputs(microgl_examples)