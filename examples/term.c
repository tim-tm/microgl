/**
 *  term.c
 *  @brief Graphical representation of commands.
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
#include <string.h>
#include "mgl.h"

static uint32_t y = 0;

void print(mgl_display *disp, const char *str) {
    if (disp == NULL) return;
    if (y >= 64) {
        y = 0;
        mgl_display_fill(disp, 0x00);
    }
    mgl_display_draw_string(disp, 0, y, str);
    mgl_display_render(disp);
    y += 8;
}

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

    printf("> ");

    char buf[512];
    memset(buf, 0, 512);
    int buf_len = 0;
    int c;
    while ((c = getchar()) != EOF) {
        if (c == '\r' || c == '\n') {
            char fmt[1024] = {0};
            snprintf(fmt, 1024, ">%s", buf);
            print(&disp, fmt);
            printf("%s\n> ", buf);

            memset(buf, 0, 512);
            buf_len = 0;
        }
        if (buf_len < 512) {
            buf[buf_len++] = c;
        }
    }

    // Free'ing resources
    mgl_display_destroy(&disp);
    return 0;
}
