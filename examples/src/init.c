#include <stdio.h>
#include "pico/stdlib.h"
#include "microgl.h"

int main(void) {
    // Configure as you wish
    mgl_display disp = {
        .core = MGL_DISPLAY_CORE_SH1106,
        .sda_pin = 0,
        .scl_pin = 1,
        .i2c_address = 0x3c,
        .i2c_baudrate = 400000,
        .width = 128,
        .height = 64,
        .framebuffer = NULL
    };

    // Handling the error mgl_display_init may return
    if (!mgl_display_init(&disp)) {
        printf("Failed to init display!\n");
        return 1;
    }

    while (1) {
        // Drawing a pixel at 100|10
        mgl_display_draw_pixel(&disp, 100, 10);
        // Drawing a line from 20|20 to 25|25
        mgl_display_draw_line(&disp, 20, 20, 25, 25);
        // Filling a rect at 5|5 of size 10|10
        mgl_display_draw_rect(&disp, 5, 5, 10, 10, true);
        // Drawing a rect outline at 50|5 of size 10|10
        mgl_display_draw_rect(&disp, 50, 5, 10, 10, false);
        // Pushing to the display
        mgl_display_render(&disp);
        // Sleeping
        sleep_ms(10000);

        // Clear the display
        mgl_display_fill(&disp, 0x00);
        // Pushing to the display
        mgl_display_render(&disp);
        // Sleeping
        sleep_ms(10000);
    }
    // Free'ing resources
    mgl_display_destroy(&disp);
    return 0;
}