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

LinkedList* new_linked_list(size_t type){
    LinkedListData* data = malloc(sizeof(LinkedListData));
    LinkedList* list = malloc(sizeof(LinkedList));
    *data = (LinkedListData){
        .length = 0,
        .type = type,
        .start = NULL,
        .end = NULL,
    };

    *list = (LinkedList){
        .data = data,
        .current_pt = NULL,
    };

    return list;
}

void linked_list_add(LinkedList* list, void* element){
    LinkedListElement* e = malloc(sizeof(LinkedListElement));
    *e = (LinkedListElement){
        .element = element,
        .previus = list->data->end,
        .next = NULL,
    };
    if(list->data->end)
        list->data->end->next = e;

    list->data->end = e;
    list->data->length += 1;

    if(!list->data->length || !list->data->start){
        list->data->start = e;
        list->current_pt = e;
    }
}

void* linked_list_pop(LinkedList* list){
    if(!list->data->length || !list->data->start || !list->data->end)
        return NULL;

    void* res = list->data->end->element;
    list->data->length -= 1;

    if(!list->data->end->previus){
        free(list->data->end);
        list->current_pt = NULL;
        list->data->start = NULL;
        list->data->end = NULL;
    }
    else{
        list->data->end = list->data->end->previus;
        free(list->data->end->next);
        list->data->end->next = NULL;
    }

    return res;
}

void* linked_list_get_pos_index(LinkedList* list, int i){
    if(i >= (int)list->data->length)
        return NULL;

    LinkedListElement* res = list->data->start;

    for(int k = 0; k < i; k++)
        res = res->next;

    return res->element;
}

void* linked_list_get_neg_index(LinkedList* list, int i){
    if(-i >= (int)list->data->length)
        return NULL;

    LinkedListElement* res = list->data->end;

    for(int k = -1; k > i; k--)
        res = res->previus;

    return res->element;
}

void* linked_list_get_index(LinkedList* list, int i){
    return i < 0 ? linked_list_get_neg_index(list, i) :
        linked_list_get_pos_index(list, i);
}

void* linked_list_increment(LinkedList* list){
    if(!list->current_pt){
        list->current_pt = list->data->start;
        return NULL;
    }

    list->current_pt = list->current_pt->next;
    return list->current_pt ? list-> current_pt->element : NULL;
}

void* linked_list_decrement(LinkedList* list){
    if(list->current_pt){
        list->current_pt = list->data->end;
        return NULL;
    }

    list->current_pt = list->current_pt->previus;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* linked_list_get_start(LinkedList* list){
    list->current_pt = list->data->start;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* linked_list_get_end(LinkedList* list){
    list->current_pt = list->data->end;
    return list->current_pt ? list->current_pt->element : NULL;
}

void free_linked_list(LinkedList* list, char FreeValues){
    void* e;
    while((e = linked_list_pop(list)))
        if(FreeValues)
            free(e);
    free(list->data);
    free(list);
}

void linked_list_insert_pos(LinkedList* list, void* element, int index){
    LinkedListElement* e = list->data->start;

    for(int k = 0; k<index; k++)
        e = e->next;

    LinkedListElement* insert = malloc(sizeof(LinkedListElement));
    *insert = (LinkedListElement){
        .element = element,
        .previus = e->previus,
        .next = e,
    };

    insert->previus->next = insert;
    insert->next->previus = insert;
}

void linked_list_insert_neg(LinkedList* list, void* element, int index){
    LinkedListElement* e = list->data->end;

    for(int k = -1; k>index; k--)
        e = e->previus;

    LinkedListElement* insert = malloc(sizeof(LinkedListElement));
    *insert = (LinkedListElement){
        .element = element,
        .previus = e,
        .next = e->next,
    };

    insert->next->previus = insert;
    insert->previus->next = insert;
}

void linked_list_insert_start(LinkedList* list, void* element){
    LinkedListElement* e = malloc(sizeof(LinkedListElement));

    *e = (LinkedListElement){
        .element = element,
        .previus = NULL,
        .next = list->data->start,
    };

    list->data->start->previus = e;
    list->data->length += 1;
    list->data->start = e;
}

void linked_list_insert(LinkedList* list, void* element, int index){
    if(index >= (int)list->data->length || index == -1 || !list->data->length)
        linked_list_add(list, element);
    else if(index == 0 || -index >= (int)list->data->length)
        linked_list_insert_start(list, element);
    else{
        if(index >= 0)
            linked_list_insert_pos(list, element, index);
        else
            linked_list_insert_neg(list, element, index);
        list->data->length += 1;
    }
}

LinkedListElement* linked_list_remove_pos(LinkedList* list, int index){
    LinkedListElement* e = list->data->start;

    for(int k=0; k<index; k++)
        e = e->next;

    return e;
}

LinkedListElement* linked_list_remove_neg(LinkedList* list, int index){
    LinkedListElement* e = list->data->end;

    for(int k =-1; k>index; k--)
        e = e->previus;

    return e;
}

void* linked_list_remove_start(LinkedList* list){
    LinkedListElement* res = list->data->start;
    list->data->start = res->next;
    list->data->start->previus = NULL;
    list->data->length -=1;
    void* e = res->element;
    free(res);
    return e;
}

void* linked_list_remove(LinkedList* list, int index){
    if(!list->data->length)
        return NULL;
    if(list->data->length == 1 || index >= (int)list->data->length || index == -1)
        return linked_list_pop(list);
    if(index == 0 || -index >= (int)list->data->length)
        return linked_list_remove_start(list);
    LinkedListElement* e;

    if(index >= 0)
        e = linked_list_remove_pos(list, index);
    else
        e = linked_list_remove_neg(list, index);

    void* res = e->element;

    list->data->length -=1;
    e->next->previus = e->previus;
    e->previus->next = e->next;

    free(e);

    return res;
}






