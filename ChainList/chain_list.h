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


#ifndef __CHAIN_LIST_H__
#define __CHAIN_LIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct CHAIN_LIST_ELEMENT_STRUCT {
    void* element;
    struct CHAIN_LIST_ELEMENT_STRUCT* previus;
    struct CHAIN_LIST_ELEMENT_STRUCT* next;
} ChainListElement;

typedef struct{
    size_t length;
    size_t type;
    ChainListElement* start;
    ChainListElement* end;
} ChainListData;

typedef struct{
    ChainListData* data;
    ChainListElement* current_pt;
} ChainList;

ChainList* new_chain_list(size_t type);

void chain_list_add(ChainList* list, void* element);

void* chain_list_pop(ChainList* list);

void* chain_list_get_index(ChainList* list, int i);

void* chain_list_increment(ChainList* list);

void* chain_list_decrement(ChainList* list);

void* chain_list_get_start(ChainList* list);

void* chain_list_get_end(ChainList* list);

void free_chain_list(ChainList* list, char FreeValues);

void chain_list_insert(ChainList* list, void* element, int index);

void* chain_list_remove(ChainList* list, int index);

#endif // __CHAIN_LIST_H__

