/**
 *  drawtest.c
 *  @brief Test of every drawing (and filling) function avalible
 * 
 *  BSD-3-Clause license:
 *    Copyright 2024 (c) Tim Teichmann and 2020 Raspberry Pi (Trading) Ltd.
 *  
 *    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 *    following conditions are met:
 *    
 *    1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 *    
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 *    
 *    3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *    
 *    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *    INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
        // Draw 'A'
        mgl_display_draw_char(&disp, 50, 35, 'A');
        // Draw 'b'
        mgl_display_draw_char(&disp, 60, 35, 'b');
        // Draw 'Abc'
        mgl_display_draw_string(&disp, 80, 35, "Abc");
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