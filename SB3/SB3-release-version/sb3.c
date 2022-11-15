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


#include "sb3.h"
#include <err.h>
#include <stdio.h>
#include <string.h>

SB3_errors_t last_error = SB3_SUCCESS_EXIT;

char* SB3_GetError(void)
{
    switch (last_error)
    {
        case SB3_NULL_PATH_ERROR:
            return "image path was NULL";
        case SB3_UNSUPORTED_BMP_FORMAT_ERROR:
            return "the bmp image passed in parameter has an unsuported format";
        case SB3_NULL_IMAGE_ERROR:
            return "image passed in parameter was NULL";
        case SB3_BAD_EXTENSION_ERROR:
            return "the path given in parameter hasn't '.bmp' extension";
        case SB3_BAD_FORMAT_ERROR:
            return "try to read an rgb image like a mono color image";
        case SB3_CORRUPTED_FILE_ERROR:
            return "try to read bmp image who doesn't have 'BM' signature at first 2 bytes";
        case SB3_CANNOT_OPEN_FILE_ERROR:
            return "cannot open given file";
        default:
            return "THERE IS NO FUCKING ERROR: WHY DO YOU WANT A MESSAGE ERROR WHEN THERE IS NO ERROR ?";
    }
}

SB3_errors_t write_image(const char* path, Image_t* image) {
    if(!image)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: NULL image cannot be saved");
        #else
            last_error = SB3_NULL_IMAGE_ERROR;
            return SB3_NULL_IMAGE_ERROR;
        #endif
    }
    if(!path)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: NULL path error");
        #else
            last_error = SB3_NULL_PATH_ERROR;
            return SB3_NULL_PATH_ERROR;
        #endif
    }
    int len = strlen(path);
    if (len <= 4 || path[len-4] != '.' || (path[len-3] != 'B' && path[len-3] != 'b') ||
            (path[len-2] != 'M' && path[len-2] != 'm') || (path[len-1] != 'P' && path[len-1] != 'p'))
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: Bad file extension (%s) (expected '.BMP' extension (with lower or upper cases))", path);
        #else
            last_error = SB3_BAD_EXTENSION_ERROR;
            return SB3_BAD_EXTENSION_ERROR;
        #endif
    }
    FILE* file;
    file = fopen(path, "wb");
    if(!file)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: Cannot open file at '%s'", path);
        #else
            last_error = SB3_CANNOT_OPEN_FILE_ERROR;
            return SB3_CANNOT_OPEN_FILE_ERROR;
        #endif
    }
    
    const int padding = ((4 - (image->w * 3) % 4) % 4);
    
    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + image->h * image->w * 3 + padding * image->h;
    
    // FILE HEADER
    uint8_t file_header[file_header_size];
    
    // signature
    file_header[0] = 'B';
    file_header[1] = 'M';
    // file size
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    // reserved 1 => UNUSED
    file_header[6] = 0;
    file_header[7] = 0;
    // reserved 2 => UNUSED
    file_header[8] = 0;
    file_header[9] = 0;
    // file offset to pixel array
    file_header[10] = file_header_size + info_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;
    
    // INFO HEADER
    uint8_t info_header[info_header_size];
    
    // info header size
    info_header[0] = info_header_size;
    info_header[1] = 0;
    info_header[2] = 0;
    info_header[3] = 0;
    // image width
    info_header[4] = image->w;
    info_header[5] = image->w >> 8;
    info_header[6] = image->w >> 16;
    info_header[7] = image->w >> 24;
    // image height
    info_header[8] = image->h;
    info_header[9] = image->h >> 8;
    info_header[10] = image->h >> 16;
    info_header[11] = image->h >> 24;
    // planes
    info_header[12] = 1;
    info_header[13] = 0;
    // bits per pixels (24 for 3 bytes(RGB))
    info_header[14] = 24;
    info_header[15] = 0;
    // compression (BI_RGB => no compression methodes => 0)
    info_header[16] = 0;
    info_header[17] = 0;
    info_header[18] = 0;
    info_header[19] = 0;
    // image size (BI_RGB => no compression methodes => 0)
    info_header[20] = 0;
    info_header[21] = 0;
    info_header[22] = 0;
    info_header[23] = 0;
    // X pixels per meter (skipped)
    info_header[24] = 0;
    info_header[25] = 0;
    info_header[26] = 0;
    info_header[27] = 0;
    // Y pixels per meter (skipped)
    info_header[28] = 0;
    info_header[29] = 0;
    info_header[30] = 0;
    info_header[31] = 0;
    // color palette (0 to default)
    info_header[32] = 0;
    info_header[33] = 0;
    info_header[34] = 0;
    info_header[35] = 0;
    // important colors (generally ignored)
    info_header[36] = 0;
    info_header[37] = 0;
    info_header[38] = 0;
    info_header[39] = 0;
    
    for(int i = 0; i < file_header_size; i++)
        fputc(file_header[i], file);
    for(int i = 0; i < info_header_size; i++)
        fputc(info_header[i], file);
    
    // IMAGE DATA
    for(int y = 0; y < image->h; y++)
    {
        for(int x = 0; x < image->w; x++)
        {
            uint8_t r, g, b;
            if(image->format == SB3_RGB_FORMAT)
            {
                RGBColor_t* color = image->rgb_pixels[y * image->w + x];
                r = color->r; g = color->g; b = color->b;
            }
            else
            {
                r = g = b = image->mono_pixels[y * image->w + x]->color;
            }
            fputc(b, file);
            fputc(g, file);
            fputc(r, file);
        }
        for(int i = 0; i < padding; i++)
            fputc(0, file);
    }
    fclose(file);
    last_error = SB3_SUCCESS_EXIT;
    return SB3_SUCCESS_EXIT;
}

Image_t* read_image(const char* path, Image_format_t format)
{
    if(!path)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: NULL path error");
        #else
            last_error = SB3_NULL_PATH_ERROR;
            return NULL;
        #endif
    }
    int len = strlen(path);
    if (len <= 4 || path[len-4] != '.' || (path[len-3] != 'B' && path[len-3] != 'b') ||
            (path[len-2] != 'M' && path[len-2] != 'm') || (path[len-1] != 'P' && path[len-1] != 'p'))
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Bad file extension (%s) (expected '.BMP' extension (with lower or upper cases))", path);
        #else
            last_error = SB3_BAD_EXTENSION_ERROR;
            return NULL;
        #endif
    }
    FILE* file;
    file = fopen(path, "rb");
    if(!file)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Cannot open file at '%s'", path);
        #else
            last_error = SB3_CANNOT_OPEN_FILE_ERROR;
            return NULL;
        #endif
    }
    
    const int file_header_size = 14;
    const int info_header_size = 40;
    
    uint8_t file_header[file_header_size];
    for(int i = 0; i < file_header_size; i++)
        file_header[i] = fgetc(file);
    
    if(file_header[0] != 'B' || file_header[1] != 'M')
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Corrupted image => 'BM' signature not present at 2 first bytes of header bmp file");
        #else
            last_error = SB3_CORRUPTED_FILE_ERROR;
            return NULL;
        #endif
    }
    
    // int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
    
    uint8_t info_header[info_header_size];
    for(int i = 0; i < info_header_size; i++)
        info_header[i] = fgetc(file);
    
    if(info_header[0] != info_header_size || info_header[1] != 0 || info_header[2] != 0 || info_header[3] != 0
        || info_header[12] != 1 || info_header[13] != 0 || info_header[14] != 24 || info_header[15] != 0)
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Unsupported bmp format");
        #else
            last_error = SB3_UNSUPORTED_BMP_FORMAT_ERROR;
            return NULL;
        #endif
    }
    for(int i = 16; i < 24; i++)
        if(info_header[i] != 0)
        {
            fclose(file);
            #ifdef SB3_CRASH_WHEN_ERROR
                errx(EXIT_FAILURE, "READ_IMAGE: Unsupported bmp compression");
            #else
                last_error = SB3_UNSUPORTED_BMP_FORMAT_ERROR;
                return NULL;
            #endif
        }
    
    int width = info_header[4] + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
    int height = info_header[8] + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);

    RGBColor_t** rgb_pixels = NULL;
    MonoColor_t** mono_pixels = NULL;
    
    if(format == SB3_RGB_FORMAT)
        rgb_pixels = malloc(width*height*sizeof(RGBColor_t*));
    else
        mono_pixels = malloc(width*height*sizeof(MonoColor_t*));

    const int padding = ((4 - (width * 3) % 4) % 4);
    
    for (int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            uint8_t r, g, b;
            b = fgetc(file);
            g = fgetc(file);
            r = fgetc(file);
            if(format == SB3_RGB_FORMAT)
            {
                RGBColor_t* color = malloc(sizeof(*color));
                *color = (RGBColor_t) {
                    .r = r,
                    .g = g,
                    .b = b,
                };
                rgb_pixels[y * width + x] = color;
            }
            else
            {
                if(r == g && g == b)
                {
                    MonoColor_t* color = malloc(sizeof(*color));
                    color->color = r;
                    mono_pixels[y * width + x] = color;
                }
                else
                {
                    fclose(file);
                    for(int i = 0; i < y * width + x; i++)
                        free(mono_pixels[i]);
                    free(mono_pixels);
                    #ifdef SB3_CRASH_WHEN_ERROR
                        errx(EXIT_FAILURE, "READ_FILE: Incorrect Mono color format");
                    #else
                        last_error = SB3_BAD_FORMAT_ERROR;
                        return NULL;
                    #endif
                }
            }
        }
        for(int i = 0; i < padding; i++)
            fgetc(file);
    }
    fclose(file);

    Image_t* image = malloc(sizeof(*image));
    *image = (Image_t) {
        .w = width,
        .h = height,
        .format = format,
        .mono_pixels = mono_pixels,
        .rgb_pixels = rgb_pixels,
    };
    
    last_error = SB3_SUCCESS_EXIT;
    return image;
}



