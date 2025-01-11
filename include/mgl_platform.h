/**
 *  mgl_platform.h
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
