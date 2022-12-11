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


#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdlib.h>

typedef struct LINKED_LIST_ELEMENT_STRUCT {
    void* element;
    struct LINKED_LIST_ELEMENT_STRUCT* previus;
    struct LINKED_LIST_ELEMENT_STRUCT* next;
} linked_list_element_t;

typedef struct{
    size_t length;
    size_t type;
    linked_list_element_t* start;
    linked_list_element_t* end;
    linked_list_element_t* current_pt;
} linked_list_t;

linked_list_t* new_linked_list(size_t type);

void linked_list_add(linked_list_t* list, void* element);

void* linked_list_pop(linked_list_t* list);

void* linked_list_get_index(linked_list_t* list, int i);

void* linked_list_increment(linked_list_t* list);

void* linked_list_decrement(linked_list_t* list);

void* linked_list_get_start(linked_list_t* list);

void* linked_list_get_end(linked_list_t* list);

void free_linked_list(linked_list_t* list, char FreeValues);

void linked_list_insert(linked_list_t* list, void* element, int index);

void* linked_list_remove(linked_list_t* list, int index);

#endif // __LINKED_LIST_H__

