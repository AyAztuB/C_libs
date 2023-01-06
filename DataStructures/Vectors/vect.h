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


#ifndef __LAMBDA_H__
#define __LAMBDA_H__

#define lambda(lambda$_ret, lambda$_args, lambda$_body) \
({ \
    lambda$_ret lambda$__anon$ lambda$_args \
        lambda$_body \
    &lambda$__anon$; \
})

#endif // __LAMBDA_H__

#ifndef __VECT_H__
#define __VECT_H__

#include <stdlib.h>
#include <stdio.h>

#define Vect(T) T*

typedef struct {
    size_t capacity;
    size_t length;
} vect_data_t;

#define Vect_init(T, capacity) \
({ \
    size_t __$capacity$__ = (size_t) (capacity); \
    vect_data_t* __$res$__ = malloc(sizeof(vect_data_t) + __$capacity$__ * sizeof(T)); \
    __$res$__->capacity = __$capacity$__; \
    __$res$__->length = 0; \
    /* RETURN */ \
    (Vect(T)) ((void*)__$res$__+sizeof(vect_data_t)); \
})

#define Vect_new(T) \
({ \
    vect_data_t* __$res$__ = malloc(sizeof(vect_data_t) + 4 * sizeof(T)); \
    __$res$__->capacity = 4; \
    __$res$__->length = 0; \
    /* RETURN */ \
    (Vect(T)) ((void*)__$res$__+sizeof(vect_data_t)); \
})

#define Vect_free(vect) \
({ \
    free((void*)vect - sizeof(vect_data_t)); \
})

#define Vect_free_content(vect) \
({ \
    vect_data_t* __$data$__ = (vect_data_t*)((void*)vect - sizeof(vect_data_t)); \
    for(size_t __$i$__ = 0; __$i$__ < __$data$__->length; __$i$__++) \
        free(vect[__$i$__]); \
    __$data$__->length = 0; \
})

#define Vect_push(vect, T, element) \
({ \
    T __$elem$__ = (T) (element); \
    vect_data_t* __$data$__ = (void*)vect - sizeof(vect_data_t); \
    if(__$data$__->length == __$data$__->capacity) { \
        __$data$__ = (vect_data_t*)realloc((void*)__$data$__, sizeof(vect_data_t) + 2*__$data$__->capacity*sizeof(T)); \
        __$data$__->capacity *= 2; \
    } \
    vect = (Vect(T)) ((void*)__$data$__ + sizeof(vect_data_t)); \
    *(vect + __$data$__->length) = __$elem$__; \
    __$data$__->length++; \
    /* RETURN */ \
    vect; \
})

#define Vect_pop(vect) \
({ \
    vect_data_t* __$data$__ = (void*)vect - sizeof(vect_data_t); \
    __$data$__->length--; \
    /* RETURN */ \
    vect[__$data$__->length]; \
})

#define Vect_length(vect) \
({ \
    /* RETURN */ \
    ((vect_data_t*)((void*)vect - sizeof(vect_data_t)))->length; \
})

#define Vect_print(vect, print_fct) \
({ \
    printf("{ "); \
    for(size_t __$i$__ = 0; __$i$__ < Vect_length(vect); __$i$__++) \
        print_fct(vect[__$i$__]); printf(" "); \
    printf("}\n"); \
})

#endif // __VECT_H__
