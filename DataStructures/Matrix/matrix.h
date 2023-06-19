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

#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define Matrix(T) T*

#define Matrix_new(T, _r, _c) \
({ \
    size_t __row = (size_t)(_r), __col = (size_t)(_c); \
    size_t* __res = malloc(2*sizeof(size_t) + __col*__row*sizeof(T)); \
    *__res = __row; *(__res+1) = __col; \
    /* RETURN */ \
    (Matrix(T)) (__res+2); \
})

#define Matrix_new_empty(T, _r, _c) \
({ \
    size_t __row = (size_t)(_r), __col = (size_t)(_c); \
    size_t* __res = malloc(2*sizeof(size_t) + __row*__col*sizeof(T)); \
    *__res = __row; *(__res+1) = __col; \
    Matrix(T) __m = (Matrix(T)) (__res+2); \
    for(size_t __i = 0; __i < __row*__col; __i++) __m[__i] = (T)0; \
    /* RETURN */ \
    __m; \
})

#define Matrix_identity(T, _n) \
({ \
    size_t __n = (size_t)(_n); \
    Matrix(T) __id = Matrix_new_empty(T, __n, __n); \
    for(size_t __i = 0; __i < __n; __i++) \
        __id[__i * __n + __i] = (T)1; \
    /* RETURN */ \
    __id; \
})

#define Matrix_copy(T, src, copy_fct) \
({ \
    size_t* __data = (size_t*)src; \
    size_t* __dst = malloc(2*sizeof(size_t) + __data[-2]*__data[-1]*sizeof(T)); \
    *__dst = __data[-2]; *(__dst+1) = __data[-1]; \
    Matrix(T) __res = (Matrix(T)) (__dst+2); \
    for(size_t __i = 0; __i < __data[-2] * __data[-1]; __i++) __res[__i] = copy_fct(src[__i]); \
    /* RETURN */ \
    __res; \
})

#define Matrix_free(matrix) \
({ \
    free(((size_t*)matrix)-2); \
})

#define Matrix_free_content(matrix) \
({ \
    size_t __row = *(((size_t*)matrix)-2), __col = *(((size_t*)matrix)-1); \
    for(size_t __i = 0; __i < __row * __col; __i++) \
        free(matrix[__i]); \
})

#define Matrix_col(matrix) \
({ \
    /* RETURN */ \
    *(((size_t*)matrix)-1); \
})

#define Matrix_row(matrix) \
({ \
    /* RETURN */ \
    *(((size_t*)matrix)-2); \
})

#define Matrix_print(matrix, print_fct) \
({ \
    printf("{\n"); \
    size_t __col = Matrix_col(matrix); \
    for(size_t __i = 0; __i < Matrix_row(matrix); __i++) \
    { \
        printf("  "); \
        for(size_t __j = 0; __j < __col; __j++) \
            print_fct(matrix[__i * __col + __j]); \
        printf("\n"); \
    } \
    printf("}\n"); \
})

// TWO MATRICES OPERATIONS

// axis=1 means combine(A(m,n), B(m,p)) => M(m,n+p) and axis=0 is for the other axisention
#define Matrix_combine(T, a, b, axis) \
({ \
    size_t __row_a = Matrix_row(a), __row_b = Matrix_row(b), __col_a = Matrix_col(a), __col_b = Matrix_col(b); \
    if(axis) assert(__row_a == __row_b); \
    else assert(__col_a == __col_b); \
    Matrix(T) __mat; \
    size_t __row_res, __col_res; \
    if(axis) { __col_res = __col_a + __col_b; __row_res = __row_a; __mat = Matrix_new(T, __row_a, __col_res); } \
    else { __row_res = __row_a + __row_b; __col_res = __col_a; __mat = Matrix_new(T, __row_res, __col_a); } \
    for(size_t __i = 0; __i < __row_res; __i++) \
        for(size_t __j = 0; __j < __col_res; __j++) \
        { \
            if(__j >= __col_a) \
                __mat[__i*__col_res+__j] = (T)(b[__i*__col_b + __j - __col_a]); \
            else if(__i >= __row_a) \
                __mat[__i*__col_res+__j] = (T)(b[(__i-__row_a)*__col_b + __j]); \
            else __mat[__i*__col_res+__j] = (T)(a[__i*__col_a+__j]); \
        } \
    /* RETURN */ \
    __mat; \
})

#define Matrix_mult(T, a, b) \
({ \
    size_t __row_a = Matrix_row(a), __row_b = Matrix_row(b), __col_a = Matrix_col(a), __col_b = Matrix_col(b); \
    assert(__col_a == __row_b); \
    Matrix(T) __res = Matrix_new_empty(T, __row_a, __col_b); \
    for(size_t __i = 0; __i < __row_a; __i++) { \
        for(size_t __j = 0; __j < __col_b; __j++) { \
            for(size_t __k = 0; __k < __col_a; __k++) \
                __res[__i * __col_b + __j] += a[__i * __col_a + __k] * b[__k * __col_b + __j]; \
        } \
    } \
    /* RETURN */ \
    __res; \
})

#define Matrix_operation(T, a, b, fct) \
({ \
    size_t __row_a = Matrix_row(a), __row_b = Matrix_row(b), __col_a = Matrix_col(a), __col_b = Matrix_col(b); \
    assert(__col_a == __col_b && __row_a == __row_b); \
    Matrix(T) __res = Matrix_new(T, __row_a, __col_a); \
    for(size_t __i = 0; __i < __row_a * __col_a; __i++) \
        __res[__i] = fct(a[__i], b[__i]); \
    /* RETURN */ \
    __res; \
})

#define Matrix_add(T, a, b) \
({ \
    /* RETURN */ \
    Matrix_operation(T, a, b, lambda(T, (T a, T b), { return a+b; })); \
})

#define Matrix_sub(T, a, b) \
({ \
    /* RETURN */ \
    Matrix_operation(T, a, b, lambda(T, (T a, T b), { return a-b; })); \
})

#define Matrix_mult_elements(T, a, b) \
({ \
    /* RETURN */ \
    Matrix_operation(T, a, b, lambda(T, (T a, T b), { return a*b; })); \
})

// ONE MATRIX AND ONE NUMBER OPERATIONS

#define Matrix_operation_with_number(T, mat, nb, fct) \
({ \
    T __nb = (T)(nb); \
    size_t __mat_row = Matrix_row(mat), __mat_col = Matrix_col(mat); \
    Matrix(T) __res = Matrix_new(T, __mat_row, __mat_col); \
    for(size_t __i = 0; __i < __mat_row * __mat_col; __i++) \
        __res[__i] = fct(mat[__i], __nb); \
    /* RETURN */ \
    __res; \
})

#define Matrix_plus_nb(T, mat, nb) \
({ \
    /* RETURN */ \
    Matrix_operation_with_number(T, mat, (T)(nb), lambda(T, (T i, T n), { return i+n; })); \
})

#define Matrix_minus_nb(T, mat, nb) \
({ \
    /* RETURN */ \
    Matrix_operation_with_number(T, mat, (T)(nb), lambda(T, (T i, T n), { return i-n; })); \
})

#define number_minus_matrix(t, mat, nb) \
({ \
    /* return */ \
    matrix_operation_with_number(t, mat, (t)(nb), lambda(T, (T i, T n), { return n-i; })); \
})

#define Matrix_mult_nb(T, mat, nb) \
({ \
    /* RETURN */ \
    Matrix_operation_with_number(T, mat, (T)(nb), lambda(T, (T i, T n), { return i*n; })); \
})

#define Matrix_divised_by_nb(T, mat, nb) \
({ \
    /* RETURN */ \
    Matrix_operation_with_number(T, mat, (T)(nb), lambda(T, (T i, T n), { return i/n; })); \
})

#define Matrix_divising_nb(T, mat, nb) \
({ \
    /* RETURN */ \
    Matrix_operation_with_number(T, mat, (T)(nb), lambda(T, (T i, T n), { return n/i; })); \
})

// ONE MATRIX OPERATIONS

#define Matrix_transpose(T, a) \
({ \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    Matrix(T) __res = Matrix_new(T, __col, __row); \
    for(size_t __i = 0; __i < __col; __i++) \
        for(size_t __j = 0; __j < __row; __j++) \
            __res[__i * __row + __j] = a[__j * __col + __i]; \
    /* RETURN */ \
    __res; \
})

#define Matrix_expend(T, a, new_row, new_col) \
({ \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    size_t __new_row = (new_row) >= 0 ? new_row : __row; \
    size_t __new_col = (new_col) >= 0 ? new_col : __col; \
    Matrix(T) __res = Matrix_new(T, __new_row, __new_col); \
    for(size_t __i = 0; __i < __new_row; __i++) \
        for(size_t __j = 0; __j < __new_col; __j++) \
            __res[__i * __new_col + __j] = __i >= __row ? 0 : (__j >= __col ? 0 : a[__i*__col+__j]); \
    /* RETURN */ \
    __res; \
})

// axis=1 means sum_compress(A(m,n)) => M(m,1) and axis=0 is for the other axisention
#define Matrix_sum_compress(T, a, axis) \
({ \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    Matrix(T) __res; \
    if(axis) __res = Matrix_new_empty(T, __row, 1); \
    else __res = Matrix_new_empty(T, 1, __col); \
    for(size_t __i = 0; __i < (axis ? __row : __col); __i++) \
        for(size_t __j = 0; __j < (axis ? __col : __row); __j++) \
            __res[__i] += a[(axis ? (__i * __col + __j) : (__j * __col + __i))]; \
    /* RETURN */ \
    __res; \
})

// axis=1 : condition fct will be applied on each row and axis=0 is for the cols
// fct(size_t index, Matrix(T) matrix) => char/bool
#define Matrix_extract(T, a, fct, axis) \
({ \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    Matrix(T) __tmp = Matrix_new(T, __row, __col); \
    size_t __nb = 0; \
    for(size_t __i = 0; __i < (axis ? __row : __col); __i++) \
    { \
        if(fct(__i, a)) \
        { \
            for(size_t __j = 0; __j < (axis ? __col : __row); __j++) \
                __tmp[(axis ? (__nb * __col + __j) : (__j * __col + __nb))] = a[(axis ? (__i * __col + __j) : (__j * __col + __i))]; \
            __nb++; \
        } \
    } \
    Matrix(T) __res = Matrix_expend(T, a, (axis ? __nb : __row), (axis ? __col : __nb)); \
    Matrix_free(__tmp); \
    /* RETURN */ \
    __res; \
})

#define Matrix_determinant(T, a) \
({ \
    Matrix(T) __mat = Matrix_copy(T, a, lambda(T, (T i), { return i; })); \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    assert(__row == __col); \
    T* __tmp = malloc(sizeof(T) * __row+1); \
    int __det = 1; \
    T __num1, __num2, __total = (T)1; \
    size_t __index; \
    for(size_t __i = 0; __i < __row; __i++) \
    { \
        __index = __i; \
        while(__index < __row && !__mat[__index * __col + __i]) __index++; \
        if(__index == __row) continue; \
        if(__index != __i) \
        { \
            for(size_t __j = 0; __j < __row; __j++) \
            { \
                T __swap_tmp = __mat[__index*__col+__j]; \
                __mat[__index*__col+__j] = __mat[__i*__col+__j]; \
                __mat[__i*__col+__j] = __swap_tmp; \
            } \
            if((__index - __i) % 2) __det *= -1; \
        } \
        for(size_t __j = 0; __j < __row; __j++) __tmp[__j] = __mat[__i*__col+__j]; \
        for(size_t __j = __i+1; __j < __row; __j++) \
        { \
            __num1 = __tmp[__i]; __num2 = __mat[__j*__col+__i]; \
            for(size_t __k = 0; __k < __row; __k++) \
                __mat[__j*__col+__k] = (__num1 * __mat[__j*__col+__k])-(__num2*__tmp[__k]); \
            __total *= __num1; \
        } \
    } \
    for(size_t __i = 0; __i < __row; __i++) __det *= (int)__mat[__i*__col+__i]; \
    Matrix_free(__mat); \
    free(__tmp); \
    /* RETURN */ \
    (__det / (int)__total); \
})

// TODO : adaptation/refund to continue

// TODO: inverse

// TODO : BELLOW : CHANGE VARIABLE NAMES AS FOLLOW: var_name => __$var_name$__

// TODO : add (void* args) in extract macro and in the lambda fct pass as
// parameter to give some information in the lambda fct...

#define Matrix_invert(T, a) \
({ \
    size_t __row = Matrix_row(a), __col = Matrix_col(a); \
    assert(__row == __col); \
    Matrix(long double) __copy = Matrix_copy(long double, a, lambda(long double, (T i), { return (long double)i; })); \
    Matrix(long double) __id = Matrix_identity(long double, __row); \
    Matrix(long double) __combine = Matrix_combine(long double, __copy, __id, 1); \
    Matrix_free(__copy); \
    Matrix_free(__id); \
    for(size_t __i = 0; __i < __row; __i++) \
    { \
        size_t __j = 1; \
        long double __pivot = __combine[__i * 2*__row + __i]; \
        while(!__pivot && __i+__j < __row) \
        { \
            for(size_t __k = 0; __k < 2*__row; __k++) \
            { \
                long double __tmp = __combine[__i*2*__row+__k]; \
                __combine[__i*2*__row+__k] = __combine[(__i+__j)*2*__row+__k]; \
                __combine[(__i+__j)*2*__row+__k] = __tmp; \
            } \
            __j++; \
            __pivot = __combine[__i*2*__row+__i]; \
        } \
        if(!__pivot) \
        { \
            /* RETURN */ /* inverse doesn't exist */ \
            NULL; \
        } \
        for(size_t __k = 0; __k < 2 * __row; __k++) \
            __combine[__i * 2 * __row + __k] /= __pivot; \
        for(size_t __k = 0; __k < __row; __k++) \
        { \
            if(__k != __i) \
            { \
                long double __mult = __combine[__k * 2 * __row + __i]; \
                for(size_t __l = 0; __l < 2 * __row; __l++) \
                { \
                    __combine[__k * 2 * __row + __l] -= __combine[__i * 2 * __row + __l] * __mult; \
                } \
            } \
        } \
    } \
    size_t* __data = malloc(2 * sizeof(size_t) + __row*__row*sizeof(long double)); \
    *__data = __row; *(__data+1) = __row; \
    Matrix(long double) __res = (Matrix(long double))(__data+2); \
    for(size_t __i = 0; __i < __row; __i++) \
        for(size_t __j = 0; __j < __row; __j++) \
            __res[__i*__row+__j] = __combine[__i*2*__row+__j+__row]; \
    Matrix_free(__combine); \
    /* RETURN */ \
    __res; \
})

#endif // __MATRIX_H__
