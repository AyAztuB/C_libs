#pragma once

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

