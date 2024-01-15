#ifndef _MICROGL_H_
#define _MICROGL_H_

#ifdef __cplusplus
extern "C" {
#endif

// Display specific constants
#define MGL_SH1106_SET_CONTRAST _u(0x81)
#define MGL_SH1106_SET_NORM_INV _u(0xa6)
#define MGL_SH1106_SET_DISPLAY _u(0xae)
#define MGL_SH1106_SET_SCAN_DIR _u(0xc0)
#define MGL_SH1106_SET_SEG_REMAP _u(0xa0)
#define MGL_SH1106_LOW_COLUMN_ADDRESS _u(0x00)
#define MGL_SH1106_HIGH_COLUMN_ADDRESS _u(0x10)
#define MGL_SH1106_SET_PAGE_ADDRESS _u(0xB0)

#include <stdint.h>
#include <stdbool.h>

// Every avalible core type
typedef enum _mgl_display_core_ {
    MGL_DISPLAY_CORE_SH1106
} mgl_display_core;

/**
 *  The majority of elements must be provided by yourself.
 *  For example:
 *  main.c
 *      mgl_display disp = {
 *          .core = MGL_DISPLAY_CORE_SH1106,
 *          .sda_pin = 0,
 *          .scl_pin = 1,
 *          .i2c_address = 0x3c,
 *          .i2c_baudrate = 400000,
 *          .width = 128,
 *          .height = 64,
 *          .framebuffer = NULL     <-- You may also allocate the framebuffer by yourself
 *      };
 *      mgl_display_init(&disp);
 */
typedef struct _mgl_display_ {
    // The core type
    mgl_display_core core;
    
    // i2c information
    uint8_t sda_pin;
    uint8_t scl_pin;
    // Many displays use 0x3c
    uint8_t i2c_address;
    uint32_t i2c_baudrate;

    // Display dimensions (in pixel)
    uint32_t width;
    uint32_t height;

    /**
     *  2D Array of pixels
     *  NOTE: mgl_display_init will only allocate this if it is NULL, 
     *       you may want to handle allocation by yourself
     */
    uint8_t* framebuffer;
} mgl_display;

/**
 *  mgl_display_init
 *
 *  @brief Initialize the display provided.
 *  NOTE: This method initializes the pico stdio and i2c.
 *  Return value:
 *      true -- success (everything was initialized properly)
 *      false -- failure (error during initialization or provided display is NULL)
 */
bool mgl_display_init(mgl_display* display);

/**
 *  mgl_display_destroy
 *  
 *  @brief Destroy an existing display
 *  NOTE: This method will only free specific items of the display, 
 *        not the pointer to the display.
 *        The framebuffer will for example be free'd (if it points to anything).
 */
void mgl_display_destroy(mgl_display* display);

/**
 *  mgl_display_write_cmd
 * 
 *  @brief Write a command to the display
 *  NOTE: This method is not intended to be used by the end-user.
 *        It is a simple abstraction of the i2c_write_blocking method from the pico stdlib.
 */
void mgl_display_write_cmd(mgl_display* display, uint8_t command);

/**
 *  mgl_display_write_data
 * 
 *  @brief Write buffer data to the display
 *  NOTE: This method is not intended to be used by the end-user.
 */
void mgl_display_write_data(mgl_display* display, uint8_t* data, uint32_t data_len);

/**
 *  mgl_display_set_state
 * 
 *  @brief Set the state of the display, aka. enable or disable it
 */
void mgl_display_set_state(mgl_display* display, bool enabled);

/**
 *  mgl_display_render
 * 
 *  @brief Render the pixels from the framebuffer onto the screen
 */
void mgl_display_render(mgl_display* display);

#ifdef __cplusplus
}
#endif
#endif // !_MICROGL_H_
