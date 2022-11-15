#include "sb3_dev.h"
#include <stdio.h>

int main(void)
{
    SB3_image_t* image = SB3_BMP_read_image("test1b.bmp", SB3_RGB_FORMAT);
    SB3_BMP_write_image("copy.bmp", image);
    return 0;
}


