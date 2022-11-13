#ifndef __SB3_H__
#define __SB3_H__

#include <stdlib.h>
#include <stdint.h>

// ENUMS

typedef enum {
    SB3_RGB_FORMAT,
    SB3_MONO_COLOR_FORMAT,
} Image_format_t;

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
} RGBColor_t;

typedef struct {
    uint8_t color;
} MonoColor_t;

typedef struct {
    int w, h;
    Image_format_t format;
    RGBColor_t** rgb_pixels;
    MonoColor_t** mono_pixels;
} Image_t;

// FUNCTIONS

char* SB3_GetError(void);
SB3_errors_t write_image(const char* path, Image_t* image);
Image_t* read_image(const char* path, Image_format_t format);

#endif // __SB3_H__
