#include "sb3_dev.h"
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

SB3_errors_t SB3_BMP_write_image(const char* path, Image_t* image) {
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


typedef struct {
    uint32_t header_size;
    uint32_t image_w;
    uint32_t image_h;
    int16_t planes;
    int16_t bit_count;
    uint32_t compression;
    uint32_t image_size;
    int32_t X_pixels_per_meter;
    int32_t Y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
} BMP_info_header_t;


Image_t* SB3_BMP_read_image(const char* path, Image_format_t format)
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
    
    uint8_t file_header[file_header_size];    
    if((file_header[0] = fgetc(file)) != 'B' || (file_header[1] = fgetc(file)) != 'M')
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Corrupted image => 'BM' signature not present at 2 first bytes of header bmp file");
        #else
            last_error = SB3_CORRUPTED_FILE_ERROR;
            return NULL;
        #endif
    }
    for(int i = 2; i < file_header_size; i++)
        file_header[i] = fgetc(file);

    // int file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
    
    const uint32_t info_header_size = fgetc(file) + (fgetc(file) << 8) + (fgetc(file) << 16) + (fgetc(file) << 24);
    if(info_header_size < 40 || info_header_size == 64)
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Unsuported bmp image format (suported: BITMAP(V[2,3,4,5])INFOHEADER))");
        #else
            last_error = SB3_UNSUPORTED_BMP_FORMAT_ERROR;
            return NULL;
        #endif
    }
    uint8_t info_header[info_header_size];
    info_header[0] = info_header_size;
    info_header[1] = info_header_size >> 8;
    info_header[2] = info_header_size >> 16;
    info_header[3] = info_header_size >> 24;
    for(uint i = 4; i < info_header_size; i++)
        info_header[i] = fgetc(file);

    /*
    if(info_header[13] != 1 || info_header[14] != 0)
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Corrupted file => color planes must be 1 :)(receved: %d)", info_header[13] + (info_header[14] << 8));
        #else
            last_error = SB3_CORRUPTED_FILE_ERROR;
            return NULL;
        #endif
    }
    */
    int width = info_header[4] + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
    int height = info_header[8] + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);

    BMP_info_header_t header = {
        .header_size = info_header_size,
        .image_w = width,
        .image_h = height,
        .planes = 1,
        .bit_count = info_header[14] + (info_header[15] << 8),
        .compression = info_header[16] + (info_header[17] << 8) + (info_header[18] << 16) + (info_header[19] << 24),
        .image_size = info_header[20] + (info_header[21] << 8) + (info_header[22] << 16) + (info_header[23] << 24),
        .X_pixels_per_meter = 0, // skipped
        .Y_pixels_per_meter = 0, // skipped
        .colors_used = info_header[32] + (info_header[33] << 8) + (info_header[34] << 16) + (info_header[35] << 24),
        .colors_important = 0, // skipped
    };
    
    if(header.compression != 0)
    {
        fclose(file);
        #ifdef SB3_CRASH_WHEN_ERROR
            errx(EXIT_FAILURE, "READ_IMAGE: Unsuported bmp image format (unsuported bmp compression)[received: %d compression value]", header.compression);
        #else
            last_error = SB3_UNSUPORTED_BMP_FORMAT_ERROR;
            return NULL;
        #endif
    }
    
    int bit_color = header.bit_count;
    if(bit_color != 1 && bit_color != 2 && bit_color != 4 && bit_color != 8 && bit_color != 24)
    {
        fclose(file);
        if(bit_color == 16 || bit_color == 32)
        {
            #ifdef SB3_CRASH_WHEN_ERROR
                errx(EXIT_FAILURE, "READ_IMAGE: Unsuported bmp image format (unsuported RGBA format (Alpha not suported))");
            #else
                last_error = SB3_UNSUPORTED_BMP_FORMAT_ERROR;
                return NULL;
            #endif
        }
        else
        {
            #ifdef SB3_CRASH_WHEN_ERROR
                errx(EXIT_FAILURE, "READ_IMAGE: Corrupted file => bit per color must be in {1,2,4,8,24} : 16 and 32 not supported");
            #else
                last_error = SB3_CORRUPTED_FILE_ERROR;
                return NULL;
            #endif
        }
    }
    
    uint8_t* color_table = NULL;
    if(header.colors_used == 0)
        header.colors_used = 2<<(bit_color - 1);
    int cool_size = header.colors_used * 4;
    if(bit_color < 16)
    {
        color_table = malloc(cool_size * sizeof(uint8_t));
        for(int i = 0; i < cool_size; i++)
            color_table[i] = fgetc(file);
    }

    RGBColor_t** rgb_pixels = NULL;
    MonoColor_t** mono_pixels = NULL;
    
    if(format == SB3_RGB_FORMAT)
        rgb_pixels = malloc(width*height*sizeof(RGBColor_t*));
    else
        mono_pixels = malloc(width*height*sizeof(MonoColor_t*));

    int padding = 0;
    if(bit_color == 24)
        padding = ((4 - (width * 3) % 4) % 4);
    else if(bit_color == 8)
        padding = width % 4;
    else if(bit_color == 4)
        padding = ((width % 2) + (width / 2)%4) % 4;
    else if(bit_color == 2)
        padding = ((width % 4) + (width / 4)%4) % 4;
    else if(bit_color == 1)
        padding = ((width % 8) + (width / 8)%4) % 4;
    
    for (int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            uint8_t r, g, b;
            if(bit_color == 24)
            {
                b = fgetc(file);
                g = fgetc(file);
                r = fgetc(file);
            }
            else
            {
                uint8_t uwu = fgetc(file);
                if(bit_color == 8)
                {
                    if(uwu >= header.colors_used)
                    {
                        free(color_table);
                        fclose(file);
                        if(format == SB3_RGB_FORMAT)
                        { for(int k = 0; k < y*width+x; k++) free(rgb_pixels[k]); free(rgb_pixels); }
                        else
                        { for(int k = 0; k < y*width+x; k++) free(mono_pixels[k]); free(mono_pixels); }
                        #ifdef SB3_CRASH_WHEN_ERROR
                            errx(EXIT_FAILURE, "READ_FILE: Corrupted color table size");
                        #else
                            last_error = SB3_CORRUPTED_FILE_ERROR;
                            return NULL;
                        #endif
                    }
                    b = color_table[uwu*4+0];
                    g = color_table[uwu*4+1];
                    r = color_table[uwu*4+2];
                }
                else
                {
                    for(int i = 0; i*bit_color < 8 && x+i < width; i++)
                    {
                        uint alcohol = uwu >> (8 - bit_color - (i * bit_color));
                        switch(bit_color)
                        {
                            case 4:
                                alcohol = alcohol & 0b1111;
                                break;
                            case 2:
                                alcohol = alcohol & 0b11;
                                break;
                            case 1:
                                alcohol = alcohol & 0b1;
                                break;
                        }
                        if(alcohol >= header.colors_used)
                        {
                            free(color_table);
                            fclose(file);
                            if(format == SB3_RGB_FORMAT)
                            { for(int k = 0; k < y*width+x+i; k++) free(rgb_pixels[k]); free(rgb_pixels); }
                            else
                            { for(int k = 0; k < y*width+x+i; k++) free(mono_pixels[k]); free(mono_pixels); }
                            #ifdef SB3_CRASH_WHEN_ERROR
                                errx(EXIT_FAILURE, "READ_FILE: Corrupted color table size (color_table_size = %d and index = %d)", header.colors_used, alcohol);
                            #else
                                last_error = SB3_CORRUPTED_FILE_ERROR;
                                return NULL;
                            #endif
                        }
                        b = color_table[alcohol*4+0];
                        g = color_table[alcohol*4+1];
                        r = color_table[alcohol*4+2];
                        if(format == SB3_RGB_FORMAT)
                        {
                            RGBColor_t* color = malloc(sizeof(*color));
                            *color = (RGBColor_t) {
                                .r = r,
                                .g = g,
                                .b = b,
                            };
                            rgb_pixels[y*width+x+i] = color;
                        }
                        else
                        {
                            if(r==g&&g==b)
                            {
                                MonoColor_t* color = malloc(sizeof(*color));
                                color->color = r;
                                mono_pixels[y*width+x+i] = color;
                            }
                            else
                            {
                                free(color_table); fclose(file);
                                for(int k = 0; k < y*width+x+i; k++)
                                    free(mono_pixels[k]);
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
                    x += 8/bit_color -1;
                    continue;
                }
            }
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
                    if(bit_color < 16)
                        free(color_table);
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
    
    if(bit_color < 16)
        free(color_table);

    last_error = SB3_SUCCESS_EXIT;
    return image;
}



