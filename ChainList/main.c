#include "chain_list.h"

int main(void){
    void* p;
    int size = sizeof(int);
    ChainList* list;
    list = new_chain_list(size);
    int* array = malloc(10*sizeof(int));
    for(int i=0; i<10; i++){
        array[i] = i;
        chain_list_add(list, (void*)&(array[i]));
    }

    printf("{ ");
    for(p = chain_list_get_start(list); p; p =chain_list_increment(list))
        printf("%d ", *((int*)(p)));
    printf("}\n");

    free_chain_list(list, 0);
    free(array);
    return 0;
}






