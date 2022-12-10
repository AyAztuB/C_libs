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


#ifndef __AYAZTUB_H__
#define __AYAZTUB_H__

// ------------------- DATA STRUCTURES --------------

#ifndef __DATA_STRUCTURES_H__
#define __DATA_STRUCTURES_H__

// ------------------- LINKED LIST -------------------

#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#include <stdlib.h>

typedef struct LINKED_LIST_ELEMENT_STRUCT {
    void* element;
    struct LINKED_LIST_ELEMENT_STRUCT* previus;
    struct LINKED_LIST_ELEMENT_STRUCT* next;
} LinkedListElement;

typedef struct{
    size_t length;
    size_t type;
    LinkedListElement* start;
    LinkedListElement* end;
} LinkedListData;

typedef struct{
    LinkedListData* data;
    LinkedListElement* current_pt;
} LinkedList;

LinkedList* new_linked_list(size_t type);

void linked_list_add(LinkedList* list, void* element);

void* linked_list_pop(LinkedList* list);

void* linked_list_get_index(LinkedList* list, int i);

void* linked_list_increment(LinkedList* list);

void* linked_list_decrement(LinkedList* list);

void* linked_list_get_start(LinkedList* list);

void* linked_list_get_end(LinkedList* list);

void free_linked_list(LinkedList* list, char FreeValues);

void linked_list_insert(LinkedList* list, void* element, int index);

void* linked_list_remove(LinkedList* list, int index);

#endif // __LINKED_LIST_H__

#endif // __DATA_STRUCTURES_H__

#endif // __AYAZTUB_H__
