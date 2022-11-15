#include "sb3_dev.h"
#include <stdio.h>

int main(void)
{
    Image_t* image = read_image("koukou.bmp", SB3_RGB_FORMAT);
    write_image("copy.bmp", image);
    return 0;
}


