/**
 *  mgl_platform.h
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
#ifndef MGL_PLATFORM_H
#define MGL_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#ifndef _u
#define _u(x) x ## u
#endif

/**
 *  mgl_platform_i2c_init
 *  TODO: Signature change: return something useful e.g. bool
 *        for error checking
 *
 *  @brief Initialize i2c for the device using the provided
 *         baudrate, sda- and scl-pin
 */
void mgl_platform_i2c_init(uint32_t baudrate, uint8_t sda_pin, uint8_t scl_pin);

/**
 *  mgl_platform_i2c_write_blocking
 *  TODO: Signature change: return something useful e.g. bool or bytes written
 *        for error checking
 *
 *  @brief Write specified data to the specified addr
 */
void mgl_platform_i2c_write_blocking(uint8_t addr, uint8_t *data, uint64_t len);

#ifdef __cplusplus
}
#endif
#endif // !MGL_PLATFORM_H
