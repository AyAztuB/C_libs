#include "sb3_dev.h"
#include <stdio.h>

int main(void)
{
    SB3_BMP_write_image("copy.bmp", SB3_BMP_read_image("koukou1b_blackandwhite.bmp", SB3_BINARY_COLOR_FORMAT));
    return 0;
}


