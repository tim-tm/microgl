cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(pico_sdk_import.cmake)

project(microgl 
    LANGUAGES C CXX ASM 
    VERSION 0.0.1 
    DESCRIPTION "Embedded graphics library"
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_library(microgl STATIC 
    src/microgl.c    
)
set_target_properties(microgl PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(microgl PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(microgl PROPERTIES PUBLIC_HEADER include/microgl.h)

include_directories(
    /usr/arm-none-eabi/include
    /usr/arm-none-eabi/include/c++/13.2.0
    /usr/arm-none-eabi/include/c++/13.2.0/arm-none-eabi
)
