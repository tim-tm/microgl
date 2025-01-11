/**
 *  mgl_platform_generic.c
 *  @brief "generic" is the default platform for microgl.
 *         It is used as a fallback and does not provide any actual implementation.
 */
#include "mgl_platform.h"

#include <assert.h>

void mgl_platform_i2c_init(uint32_t baudrate, uint8_t sda_pin, uint8_t scl_pin) {
    assert(0 && "mgl_platform_i2c_init is not implemented because microgl was compiled for platform 'generic'");
}

void mgl_platform_i2c_write_blocking(uint8_t addr, uint8_t *data, uint64_t len) {
    assert(0 && "mgl_platform_i2c_write_blocking is not implemented because microgl was compiled for platform 'generic'");
}
