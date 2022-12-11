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


#include "linked_list.h"

linked_list_t* new_linked_list(size_t type){
    linked_list_t* list = malloc(sizeof(linked_list_t));

    *list = (linked_list_t){
        .length = 0,
        .type = type,
        .start = NULL,
        .end = NULL,
        .current_pt = NULL,
    };

    return list;
}

void linked_list_add(linked_list_t* list, void* element){
    linked_list_element_t* e = malloc(sizeof(linked_list_element_t));
    *e = (linked_list_element_t){
        .element = element,
        .previus = list->end,
        .next = NULL,
    };
    if(list->end)
        list->end->next = e;

    list->end = e;
    list->length += 1;

    if(!list->length || !list->start){
        list->start = e;
        list->current_pt = e;
    }
}

void* linked_list_pop(linked_list_t* list){
    if(!list->length || !list->start || !list->end)
        return NULL;

    void* res = list->end->element;
    list->length -= 1;

    if(!list->end->previus){
        free(list->end);
        list->current_pt = NULL;
        list->start = NULL;
        list->end = NULL;
    }
    else{
        list->end = list->end->previus;
        free(list->end->next);
        list->end->next = NULL;
    }

    return res;
}

void* linked_list_get_pos_index(linked_list_t* list, int i){
    if(i >= (int)list->length)
        return NULL;

    linked_list_element_t* res = list->start;

    for(int k = 0; k < i; k++)
        res = res->next;

    return res->element;
}

void* linked_list_get_neg_index(linked_list_t* list, int i){
    if(-i >= (int)list->length)
        return NULL;

    linked_list_element_t* res = list->end;

    for(int k = -1; k > i; k--)
        res = res->previus;

    return res->element;
}

void* linked_list_get_index(linked_list_t* list, int i){
    return i < 0 ? linked_list_get_neg_index(list, i) :
        linked_list_get_pos_index(list, i);
}

void* linked_list_increment(linked_list_t* list){
    if(!list->current_pt){
        list->current_pt = list->start;
        return NULL;
    }

    list->current_pt = list->current_pt->next;
    return list->current_pt ? list-> current_pt->element : NULL;
}

void* linked_list_decrement(linked_list_t* list){
    if(list->current_pt){
        list->current_pt = list->end;
        return NULL;
    }

    list->current_pt = list->current_pt->previus;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* linked_list_get_start(linked_list_t* list){
    list->current_pt = list->start;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* linked_list_get_end(linked_list_t* list){
    list->current_pt = list->end;
    return list->current_pt ? list->current_pt->element : NULL;
}

void free_linked_list(linked_list_t* list, char FreeValues){
    void* e;
    while((e = linked_list_pop(list)))
        if(FreeValues)
            free(e);
    free(list);
}

void linked_list_insert_pos(linked_list_t* list, void* element, int index){
    linked_list_element_t* e = list->start;

    for(int k = 0; k<index; k++)
        e = e->next;

    linked_list_element_t* insert = malloc(sizeof(linked_list_element_t));
    *insert = (linked_list_element_t){
        .element = element,
        .previus = e->previus,
        .next = e,
    };

    insert->previus->next = insert;
    insert->next->previus = insert;
}

void linked_list_insert_neg(linked_list_t* list, void* element, int index){
    linked_list_element_t* e = list->end;

    for(int k = -1; k>index; k--)
        e = e->previus;

    linked_list_element_t* insert = malloc(sizeof(linked_list_element_t));
    *insert = (linked_list_element_t){
        .element = element,
        .previus = e,
        .next = e->next,
    };

    insert->next->previus = insert;
    insert->previus->next = insert;
}

void linked_list_insert_start(linked_list_t* list, void* element){
    linked_list_element_t* e = malloc(sizeof(linked_list_element_t));

    *e = (linked_list_element_t){
        .element = element,
        .previus = NULL,
        .next = list->start,
    };

    list->start->previus = e;
    list->length += 1;
    list->start = e;
}

void linked_list_insert(linked_list_t* list, void* element, int index){
    if(index >= (int)list->length || index == -1 || !list->length)
        linked_list_add(list, element);
    else if(index == 0 || -index >= (int)list->length)
        linked_list_insert_start(list, element);
    else{
        if(index >= 0)
            linked_list_insert_pos(list, element, index);
        else
            linked_list_insert_neg(list, element, index);
        list->length += 1;
    }
}

linked_list_element_t* linked_list_remove_pos(linked_list_t* list, int index){
    linked_list_element_t* e = list->start;

    for(int k=0; k<index; k++)
        e = e->next;

    return e;
}

linked_list_element_t* linked_list_remove_neg(linked_list_t* list, int index){
    linked_list_element_t* e = list->end;

    for(int k =-1; k>index; k--)
        e = e->previus;

    return e;
}

void* linked_list_remove_start(linked_list_t* list){
    linked_list_element_t* res = list->start;
    list->start = res->next;
    list->start->previus = NULL;
    list->length -=1;
    void* e = res->element;
    free(res);
    return e;
}

void* linked_list_remove(linked_list_t* list, int index){
    if(!list->length)
        return NULL;
    if(list->length == 1 || index >= (int)list->length || index == -1)
        return linked_list_pop(list);
    if(index == 0 || -index >= (int)list->length)
        return linked_list_remove_start(list);
    linked_list_element_t* e;

    if(index >= 0)
        e = linked_list_remove_pos(list, index);
    else
        e = linked_list_remove_neg(list, index);

    void* res = e->element;

    list->length -=1;
    e->next->previus = e->previus;
    e->previus->next = e->next;

    free(e);

    return res;
}






