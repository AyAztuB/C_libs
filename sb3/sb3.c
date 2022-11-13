#include "sb3.h"
#include <err.h>
#include <stdio.h>
#include <string.h>

SB3_errors_t last_error = SB3_SUCCESS_EXIT;


SB3_errors_t write_image(const char* path, Image_t* image) {
    if(!image)
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: NULL image cannot be saved\n");
        #else
            last_error = SB3_NULL_IMAGE_ERROR;
            return SB3_NULL_IMAGE_ERROR;
        #endif
    }
    int len = strlen(path);
    if (len <= 4 || path[len-4] != '.' || (path[len-3] != 'B' && path[len-3] != 'b') ||
            (path[len-2] != 'M' && path[len-2] != 'm') || (path[len-1] != 'P' && path[len-1] != 'p'))
    {
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "WRITE_IMAGE: Bad file extension (%s) (expected '.BMP' extension (with lower or upper cases))\n", path);
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
            errx(EXIT_FAILURE, "WRITE_IMAGE: Cannot open file at '%s'\n", path);
        #else
            last_error = SB3_CANNOT_OPEN_FILE_ERROR;
            return SB3_CANNOT_OPEN_FILE_ERROR;
        #endif
    }
    
    const int padding_amount = ((4 - (image->w * 3) % 4) % 4);
    
    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + image->h * image->w * 3 + padding_amount * image->h;
    
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
        for(int i = 0; i < padding_amount; i++)
            fputc(0, file);
    }
    fclose(file);
    last_error = SB3_SUCCESS_EXIT;
    return SB3_SUCCESS_EXIT;
}



