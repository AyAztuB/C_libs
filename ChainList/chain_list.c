#include <stdlib.h>
#include <stdio.h>

typedef struct{
    void* element;
    void* previus;
    void* next;
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

ChainList* new_chain_list(size_t type){
    ChainListData* data = malloc(sizeof(ChainListData));
    ChainList* list = malloc(sizeof(ChainList));
    *data = (ChainListData){
        .length = 0,
        .type = type,
        .start = NULL,
        .end = NULL,
    };

    *list = (ChainList){
        .data = data,
        .current_pt = NULL,
    };

    return list;
}

void chain_list_add(ChainList* list, void* element){
    ChainListElement* e = malloc(sizeof(ChainListElement));
    *e = (ChainListElement){
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

void* chain_list_pop(ChainList* list){
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

void* chain_list_get_pos_index(ChainList* list, int i){
    if(i >= (int)list->data->length)
        return NULL;

    ChainListElement* res = list->data->start;

    for(int k = 0; k < i; k++)
        res = res->next;

    return res->element;
}

void* chain_list_get_neg_index(ChainList* list, int i){
    if(-i >= (int)list->data->length)
        return NULL;

    ChainListElement* res = list->data->end;

    for(int k = -1; k > i; k--)
        res = res->previus;

    return res->element;
}

void* chain_list_get_index(ChainList* list, int i){
    return i < 0 ? chain_list_get_neg_index(list, i) :
        chain_list_get_pos_index(list, i);
}

void* chain_list_increment(ChainList* list){
    if(!list->current_pt){
        list->current_pt = list->data->start;
        return NULL;
    }

    list->current_pt = list->current_pt->next;
    return list->current_pt ? list-> current_pt->element : NULL;
}

void* chain_list_decrement(ChainList* list){
    if(list->current_pt){
        list->current_pt = list->data->end;
        return NULL;
    }

    list->current_pt = list->current_pt->previus;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* chain_list_get_start(ChainList* list){
    list->current_pt = list->data->start;
    return list->current_pt ? list->current_pt->element : NULL;
}

void* chain_list_get_end(ChainList* list){
    list->current_pt = list->data->end;
    return list->current_pt ? list->current_pt->element : NULL;
}

void free_chain_list(ChainList* list, char FreeValues){
    void* e;
    while((e = chain_list_pop(list)))
        if(FreeValues)
            free(e);
    free(list->data);
    free(list);
}

void chain_list_insert_pos(ChainList* list, void* element, int index){
    ChainListElement* e = list->data->start;

    for(int k = 0; k<index; k++)
        e = e->next;

    ChainListElement* insert = malloc(sizeof(ChainListElement));
    *insert = (ChainListElement){
        .element = element,
        .previus = e->previus,
        .next = e,
    };

    ((ChainListElement*)insert->previus)->next = insert;
    ((ChainListElement*)insert->next)->previus = insert;
}

void chain_list_insert_neg(ChainList* list, void* element, int index){
    ChainListElement* e = list->data->end;

    for(int k = -1; k>index; k--)
        e = e->previus;

    ChainListElement* insert = malloc(sizeof(ChainListElement));
    *insert = (ChainListElement){
        .element = element,
        .previus = e,
        .next = e->next,
    };

    ((ChainListElement*)insert->next)->previus = insert;
    ((ChainListElement*)insert->previus)->next = insert;
}

void chain_list_insert_start(ChainList* list, void* element){
    ChainListElement* e = malloc(sizeof(ChainListElement));

    *e = (ChainListElement){
        .element = element,
        .previus = NULL,
        .next = list->data->start,
    };

    list->data->start->previus = e;
    list->data->length += 1;
    list->data->start = e;
}

void chain_list_insert(ChainList* list, void* element, int index){
    if(index >= (int)list->data->length || index == -1 || !list->data->length)
        chain_list_add(list, element);
    else if(index == 0 || -index >= (int)list->data->length)
        chain_list_insert_start(list, element);
    else{
        if(index >= 0)
            chain_list_insert_pos(list, element, index);
        else
            chain_list_insert_neg(list, element, index);
        list->data->length += 1;
    }
}

ChainListElement* chain_list_remove_pos(ChainList* list, int index){
    ChainListElement* e = list->data->start;

    for(int k=0; k<index; k++)
        e = e->next;

    return e;
}

ChainListElement* chain_list_remove_neg(ChainList* list, int index){
    ChainListElement* e = list->data->end;

    for(int k =-1; k>index; k--)
        e = e->previus;

    return e;
}

void* chain_list_remove_start(ChainList* list){
    ChainListElement* res = list->data->start;
    list->data->start = res->next;
    list->data->start->previus = NULL;
    list->data->length -=1;
    void* e = res->element;
    free(res);
    return e;
}

void* chain_list_remove(ChainList* list, int index){
    if(!list->data->length)
        return NULL;
    if(list->data->length == 1 || index >= (int)list->data->length || index == -1)
        return chain_list_pop(list);
    if(index == 0 || -index >= (int)list->data->length)
        return chain_list_remove_start(list);
    ChainListElement* e;

    if(index >= 0)
        e = chain_list_remove_pos(list, index);
    else
        e = chain_list_remove_neg(list, index);

    void* res = e->element;

    list->data->length -=1;
    ((ChainListElement*)e->next)->previus = e->previus;
    ((ChainListElement*)e->previus)->next = e->next;

    free(e);

    return res;
}






