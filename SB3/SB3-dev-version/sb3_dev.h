#ifndef __SB3_H__
#define __SB3_H__

#include <stdlib.h>
#include <stdint.h>

#define SB3_DEV_VERSION "1.20"

// ENUMS

typedef enum {
    SB3_RGB_FORMAT,
    SB3_MONO_COLOR_FORMAT,
    SB3_BINARY_COLOR_FORMAT, // only white and black
} SB3_image_format_t;

typedef enum {
    SB3_SUCCESS_EXIT,
    SB3_CANNOT_OPEN_FILE_ERROR,
    SB3_CORRUPTED_FILE_ERROR,
    SB3_BAD_FORMAT_ERROR,
    SB3_BAD_EXTENSION_ERROR,
    SB3_NULL_IMAGE_ERROR,
    SB3_UNSUPORTED_BMP_FORMAT_ERROR,
    SB3_NULL_PATH_ERROR,
} SB3_errors_t;

// STRUCTS

typedef struct {
    uint8_t r, g, b;
} SB3_RGBColor_t;

typedef struct {
    uint8_t color;
} SB3_monoColor_t;

typedef struct {
    int w, h;
    SB3_image_format_t format;
    SB3_RGBColor_t** rgb_pixels;
    SB3_monoColor_t** mono_pixels;
} SB3_image_t;

// FUNCTIONS

char* SB3_GetError(void);
SB3_errors_t SB3_BMP_write_image(const char* path, SB3_image_t* image);
SB3_image_t* SB3_BMP_read_image(const char* path, SB3_image_format_t format);

#endif // __SB3_H__
