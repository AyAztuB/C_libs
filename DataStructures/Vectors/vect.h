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


#ifndef __VECT_H__
#define __VECT_H__

#include <stdlib.h>

#define Vect(T) T*

typedef struct {
    size_t capacity;
    size_t length;
    size_t element_size;
} vect_data_t;

#define Vect_init(T, capacity) \
({ \
    vect_data_t* res = malloc(sizeof(vect_data_t) + capacity * sizeof(T)); \
    res->capacity = capacity; \
    res->length = 0; \
    res->element_size = sizeof(T); \
    /* RETURN */ \
    (Vect(T)) ((void*)res+sizeof(vect_data_t)); \
})

#define Vect_new(T) \
({ \
    vect_data_t* res = malloc(sizeof(vect_data_t) + 4 * sizeof(T)); \
    res->capacity = 4; \
    res->length = 0; \
    res->element_size = sizeof(T); \
    /* RETURN */ \
    (Vect(T)) ((void*)res+sizeof(vect_data_t)); \
})

#define Vect_free(vect) \
({ \
    free((void*)vect - sizeof(vect_data_t)); \
})

#define Vect_free_content(vect) \
({ \
    vect_data_t* data = (vect_data_t*)((void*)vect - sizeof(vect_data_t)); \
    for(int i = 0; i < data->length; i++) \
        free(vect[i]); \
    data->length = 0; \
})

#define Vect_push(vect, T, element) \
({ \
    vect_data_t* data = (void*)vect - sizeof(vect_data_t); \
    if(data->length == data->capacity) { \
        data = (vect_data_t*)realloc((void*)data, sizeof(vect_data_t) + 2*data->capacity*data->element_size); \
        data->capacity *= 2; \
    } \
    vect = (Vect(T)) ((void*)data + sizeof(vect_data_t)); \
    *(vect + data->length) = element; \
    data->length++; \
    /* RETURN */ \
    vect; \
})

#define Vect_pop(vect) \
({ \
    vect_data_t* data = (void*)vect - sizeof(vect_data_t); \
    data->length--; \
    /* RETURN */ \
    vect[data->length]; \
})

#define Vect_length(vect) \
({ \
    /* RETURN */ \
    ((vect_data_t*)((void*)vect - sizeof(vect_data_t)))->length; \
})

#endif // __VECT_H__
