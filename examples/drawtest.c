/**
 *  drawtest.c
 *  @brief Test of every drawing (and filling) function avalible
 *
 *
 *  MIT License:
 *    Copyright (c) 2025 Tim Teichmann
 *    
 *    Permission is hereby granted, free of charge, to any person obtaining a copy
 *    of this software and associated documentation files (the "Software"), to deal
 *    in the Software without restriction, including without limitation the rights
 *    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the Software is
 *    furnished to do so, subject to the following conditions:
 *    
 *    The above copyright notice and this permission notice shall be included in all
 *    copies or substantial portions of the Software.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *    SOFTWARE.
 */

#include <stdio.h>
#include "mgl.h"

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
        // Draw 'A'
        mgl_display_draw_char(&disp, 50, 35, 'A');
        // Draw 'b'
        mgl_display_draw_char(&disp, 60, 35, 'b');
        // Draw 'Abc'
        mgl_display_draw_string(&disp, 80, 35, "Abc");
        // Pushing to the display
        mgl_display_render(&disp);
        // Sleeping
        // sleep_ms(10000);

        // Clear the display
        mgl_display_fill(&disp, 0x00);
        // Pushing to the display
        mgl_display_render(&disp);
        // Sleeping
        // sleep_ms(10000);
    }
    // Free'ing resources
    mgl_display_destroy(&disp);
    return 0;
}
