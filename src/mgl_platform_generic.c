/**
 *  mgl_platform_generic.c
 *  @brief "generic" is the default platform for microgl.
 *         It is used as a fallback and does not provide any actual implementation.
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
#include "mgl_platform.h"

#include <assert.h>

void mgl_platform_i2c_init(uint32_t baudrate, uint8_t sda_pin, uint8_t scl_pin) {
    assert(0 && "mgl_platform_i2c_init is not implemented because microgl was compiled for platform 'generic'");
}

void mgl_platform_i2c_write_blocking(uint8_t addr, uint8_t *data, uint64_t len) {
    assert(0 && "mgl_platform_i2c_write_blocking is not implemented because microgl was compiled for platform 'generic'");
}
