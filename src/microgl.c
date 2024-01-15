#include "microgl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

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
        display->framebuffer = calloc(display->width * display->height, sizeof(int8_t));
        if (!display->framebuffer) {
            printf("Failed to allocate framebuffer: No memory!\n");
            return false;
        }
    }
    return true;
#endif
}

void mgl_display_destroy(mgl_display* display) {
    if (display) {
        if (display->framebuffer) {
            free(display->framebuffer);
        }
    }
}

void mgl_display_write_cmd(mgl_display* display, uint8_t command) {
    if (display) {
        uint8_t buf[2] = {0x80, command};
        i2c_write_blocking(i2c_default, display->i2c_address, buf, 2, false);
    }
}

void mgl_display_write_data(mgl_display* display, uint8_t* data, uint32_t data_len) {
    if (display) {
        uint8_t* buf = malloc(data_len+1);
        if (!buf) {
            printf("Failed to write data: No memory!\n");
            return;
        }

        buf[0] = 0x40;
        memcpy(buf+1, buf, data_len);
        i2c_write_blocking(i2c_default, display->i2c_address, buf, data_len+1, false);
        free(buf);
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
        for (uint32_t i = 0; i < (display->height / 8); ++i) {
            mgl_display_write_cmd(display, MGL_SH1106_SET_PAGE_ADDRESS | i);
            mgl_display_write_cmd(display, MGL_SH1106_LOW_COLUMN_ADDRESS | 2);
            mgl_display_write_cmd(display, MGL_SH1106_HIGH_COLUMN_ADDRESS | 0);
            mgl_display_write_data(display, &display->framebuffer[display->width * i], display->width);
        }
    } break;
    default: {
        printf("Failed to render: Unknown core!\n");
    } break;
    }
}