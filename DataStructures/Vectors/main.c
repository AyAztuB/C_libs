#include "vect.h"
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    Vect(int) v = Vect_new(int);
    for(int i = 0; i < 10; i++)
        v = Vect_add(v, int, i);
    printf("length v = %lu\n", Vect_length(v));
    printf("v = {");
    for(int i = 0; i < (int)Vect_length(v); i++)
        printf(" %d", v[i]);
    printf(" }\n");
    printf("v.pop() = %d\n", Vect_pop(v));
    printf("length v = %lu\nv = {", Vect_length(v));
    for(int i = 0; i < (int)Vect_length(v); i++)
        printf(" %d", v[i]);
    printf(" }\n");
    Vect_free(v);
    return 0;
}
