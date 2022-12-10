#include <ayaztub/data_structures/linked_list.h>
#include <stdio.h>

int main(void){
    void* p;
    int size = sizeof(int);
    LinkedList* list;
    list = new_linked_list(size);
    int* array = malloc(10*sizeof(int));
    for(int i=0; i<10; i++){
        array[i] = i;
        linked_list_add(list, (void*)&(array[i]));
    }

    printf("{ ");
    for(p = linked_list_get_start(list); p; p =linked_list_increment(list))
        printf("%d ", *((int*)(p)));
    printf("}\n");

    free_linked_list(list, 0);
    free(array);
    return 0;
}






