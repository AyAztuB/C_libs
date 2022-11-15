/*
 *
 * MIT License
 *
 * Copyright (c) 2022 AyAztuB
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * AUTHOR
 *
 * AyAztuB (ayaztub@gmail.com) from https://github.com/AyAztuB/C_libs
 *
 */


#ifndef __SB3_H__
#define __SB3_H__

#include <stdlib.h>
#include <stdint.h>

#define SB3_VERSION "1.00"

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
