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

#define Vect_length(vect$__len) \
({ \
    /* RETURN */ \
    *((size_t*)(((char*)vect$__len)-2*sizeof(size_t))); \
})

#define Vect_print(vect$__print, fct$__print) \
({ \
    printf("{ "); \
    for(size_t __i$__print = 0; __i$__print < Vect_length(vect$__print); __i$__print++) \
    { fct$__print(vect$__print[__i$__print]); printf(" "); } \
    printf("}\n"); \
})

#define Vect_init(T, capacity$__init) \
({ \
    size_t __cap$__init = (size_t) (capacity$__init); \
    void* __res$__init = malloc(sizeof(size_t)*2+__cap$__init*sizeof(T)); \
    *((size_t*)__res$__init) = 0; /* length */ \
    *(((size_t*)__res$__init)+1) = __cap$__init; /* capacity */ \
    /* RETURN */ \
    (Vect(T)) (((size_t*)__res$__init)+2); \
})

#define Vect_new(T) \
({ \
    /* RETURN */ \
    Vect_init(T, 4); \
})

#define Vect_free(vect$__free) \
({ \
    free(((size_t*)vect$__free)-2); \
})

#define Vect_free_content(vect$__freecontent) \
({ \
    size_t __len$__freecontent = Vect_length(vect$__freecontent); \
    for(size_t __i$__freecontent = 0; __i$__freecontent < __len$__freecontent; __i$__freecontent++) \
        free(vect$__freecontent[__i$__freecontent]); \
    *((size_t*)(((size_t*)vect$__freecontent)-2)) = 0; \
})

#define Vect_push(vect$__push, T, element$__push) \
({ \
    T __elem$__push = (T) (element$__push); \
    size_t* __data$__push = (size_t*)(((size_t*)vect$__push)-2); \
    if(*__data$__push == *(__data$__push+1)) { \
        size_t __cap$__push = *__data$__push; \
        __data$__push = (size_t*)realloc((void*)__data$__push, 2*sizeof(size_t)+2*__cap$__push*sizeof(T)); \
        *(__data$__push+1) *= 2; \
    } \
    Vect(T) __vect$__push = (Vect(T)) (((size_t*)__data$__push)+2); \
    *(__vect$__push + *__data$__push) = __elem$__push; \
    *__data$__push += 1; \
    /* RETURN  */ \
    __vect$__push; \
})

#define Vect_pop(vect$__pop) \
({ \
    size_t* __len_ptr$__pop = (size_t*)(((size_t*)vect$__pop)-2); \
    *__len_ptr$__pop -= 1; \
    /* RETURN */ \
    vect$__pop[*__len_ptr$__pop]; \
})

#endif // __VECT_H__
