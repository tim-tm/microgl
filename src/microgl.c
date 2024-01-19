/**
 *  microgl.c
 *  @brief Microgl is an embedded graphics library for the Raspberry PI Pico.
 *         It aims to provide access to different displays, such as for example sh1106 based displays. 
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

#include "microgl.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

static void mgl_display_write_cmd(mgl_display* display, uint8_t command) {
    if (display) {
        uint8_t buf[2] = {0x80, command};
        i2c_write_blocking(i2c_default, display->i2c_address, buf, 2, false);
    }
}

bool mgl_display_init(mgl_display* display) {
    if (!display) {
        return false;
    }

    stdio_init_all();
#ifndef i2c_default
#warning "i2c_default was not defined => Pico has no i2c pins!"
    return false;
#else
    i2c_init(i2c_default, display->i2c_baudrate);
    gpio_set_function(display->sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(display->scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(display->sda_pin);
    gpio_pull_up(display->scl_pin);

    if (!display->framebuffer) {
        display->framebuffer = malloc(display->width * display->height * sizeof(uint8_t));
        if (!display->framebuffer) {
            printf("Failed to allocate framebuffer: No memory!\n");
            return false;
        }
        memset(display->framebuffer, 0x00, display->width * display->height * sizeof(uint8_t));
    }
    mgl_display_set_state(display, 1);
    mgl_display_render(display);
    return true;
#endif
}

void mgl_display_destroy(mgl_display* display) {
    if (display) {
        if (display->framebuffer) {
            free(display->framebuffer);
        }
        mgl_display_set_state(display, 0);
    }
}

void mgl_display_write_data(mgl_display* display, uint8_t data) {
    if (display) {
        uint8_t buf[2] = {0x40, data};
        i2c_write_blocking(i2c_default, display->i2c_address, buf, 2, false);
    }
}

void mgl_display_set_state(mgl_display* display, bool enabled) {
    if (!display) return;
    
    switch (display->core)
    {
    case MGL_DISPLAY_CORE_SH1106: {
        if (enabled) {
            mgl_display_write_cmd(display, MGL_SH1106_SET_DISPLAY | 0x01);
        } else {
            mgl_display_write_cmd(display, MGL_SH1106_SET_DISPLAY | 0x00);
        }
    } break;
    default: {
        printf("Failed to set state: Unknown core!\n");
    } break;
    }
}

void mgl_display_render(mgl_display* display) {
    if (!display) return;

    switch (display->core)
    {
    case MGL_DISPLAY_CORE_SH1106: {
        uint32_t pages = floor(display->height / 8);

        for (uint32_t i = 0; i < pages; ++i) {
            mgl_display_write_cmd(display, MGL_SH1106_SET_PAGE_ADDRESS | i);
            mgl_display_write_cmd(display, MGL_SH1106_LOW_COLUMN_ADDRESS);
            mgl_display_write_cmd(display, MGL_SH1106_HIGH_COLUMN_ADDRESS);
            
            uint8_t data[display->width+1] = {};
            data[0] = 0x40;
            memcpy(&data[1], &display->framebuffer[display->width*i], (display->width+1));
            i2c_write_blocking(i2c_default, display->i2c_address, data, display->width+1, false);
        }
    } break;
    default: {
        printf("Failed to render: Unknown core!\n");
    } break;
    }
}

void mgl_display_draw_pixel(mgl_display* display, uint32_t x, uint32_t y) {
    if (!display || !display->framebuffer || x >= display->width || y >= display->height) {
        return;
    }
    display->framebuffer[x + (y/8) * display->width] |= 1 << (y % 8);
}