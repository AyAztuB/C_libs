# DOCUMENTATION

## SYNOPSIS

`#include <ayaztub/data_structures/vect.h>`

content : an implementation of vectors using generic types

call `man ayaztub.data_structures.vect` for more informations

## DESCRIPTION

### Contains

The header file also contains a macro to define lambda function:
`lambda(return_type, args, body)`
It can be used like in the following exemple:
```
int (*lambda_fct) (int) = lambda(int, (int e), { printf("%d\n", e); return e; });
```

### Struct

- vect\_data\_t

### Define

* Vect(T) T\*

### Defines as functions

|return|function name|arguments|description|
|------|-------------|---------|-----------|
|Vect(T)|Vect\_init|T: type, capacity: int|create and return a new vector with capacity for initial capacity|
|Vect(T)|Vect\_new|T: type|create a new vector inisialised with a capacity of 4 and return it|
|void|Vect\_free|vect: Vect(T)|free the vector|
|void|Vect\_free\_content|vect: Vect(T)|free each element in the vector (usefull if the content was the result of a malloc, ...). The vector isn't free and can be used again.|
|Vect(T)|Vect\_push|vect: Vect(T), T: type, element: T|add element at the end of the vector and realloc if vector size is equal to vector capacity (doubling its capacity). return the new vector (usefull after a realloc)|
|T|Vect\_pop|vect: Vect(T)|return the last element in the vector and reducing its size|
|size\_t|Vect\_length|vect: Vect(T)|return the length of the vector|
|void|Vect\_print|vect: Vect(T), print\_fct: void (*print\_fct)(T)|print the vector vect using the print\_fct function to print each element|

