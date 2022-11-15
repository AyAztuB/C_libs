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


#include "sb3_dev.h"
#include <err.h>


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
            return "the format precised wasn't correct";
        case SB3_CORRUPTED_FILE_ERROR:
            return "try to read bmp image who doesn't have 'BM' signature at first 2 bytes";
        case SB3_CANNOT_OPEN_FILE_ERROR:
            return "cannot open given file";
        default:
            return "THERE IS NO FUCKING ERROR: WHY DO YOU WANT A MESSAGE ERROR WHEN THERE IS NO ERROR ?";
    }
}

void SB3_SetError(SB3_errors_t error)
{
    last_error = error;
}

