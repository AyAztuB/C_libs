#include "sb3.h"
#include <stdio.h>
#include <err.h>

int main(void)
{
    /* GENERATE IMAGE
    Image_t* image = malloc(sizeof(*image));
    image->format = SB3_RGB_FORMAT;
    image->h = 480;
    image->w = 640;
    image->mono_pixels = NULL;
    image->rgb_pixels = malloc(image->h * image->w * sizeof(RGBColor_t*));

    for(int y = 0; y < image->h; y++)
    {
        for(int x = 0; x < image->w; x++)
        {
            RGBColor_t* color = malloc(sizeof(*color));
            *color = (RGBColor_t) {
                .r = ((float)x / (float)image->w) * 255.,
                .g = (1. - ((float)x / (float)image->w)) * 255.,
                .b = ((float)y / (float)image->h) * 255,
            };
            image->rgb_pixels[y * image->w + x] = color;
        }
    }
    return write_image("test.bmp", image);
    */
    Image_t* image = read_image("test.bmp", SB3_RGB_FORMAT);
    if(!image)
        errx(EXIT_FAILURE, "%s", SB3_GetError());
    if(write_image("copy.bmp", image))
        errx(EXIT_FAILURE, "%s", SB3_GetError());
    return EXIT_SUCCESS;
}


