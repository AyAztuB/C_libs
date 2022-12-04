#include <sb3_dev.h>
#include <stdio.h>
#include <err.h>

int main(void)
{
    SB3_DEV_image_t* img = SB3_DEV_BMP_read_image("test8b.bmp", SB3_DEV_RGB_FORMAT);
    SB3_DEV_image_t* copy = SB3_DEV_grayscale(img, 0);
    SB3_DEV_BMP_write_image("copy.bmp", copy);
    SB3_DEV_FreeImage(img);
    SB3_DEV_FreeImage(copy);
    return 0;
}


