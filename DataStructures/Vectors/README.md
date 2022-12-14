# DOCUMENTATION

## SYNOPSIS

`#include <ayaztub/data_structures/vect.h>`

content : an implementation of vectors using generic types

call `man ayaztub.data_structures.vect` for more informations

## DESCRIPTION

### Struct

- vect\_data\_t

### Define

* Vect(type\_t) type\_t\*

### Defines as functions

|return|function name|arguments|description|
|------|-------------|---------|-----------|
|Vect(T)|Vect\_new|T: type|create a new vector inisialised with a capacity of 4 and return it|
|void|Vect\_free|vect: Vect(T)|free the vector|
|void|Vect\_free\_content|vect: Vect(T)|free each element in the vector (usefull if the content was the result of a malloc, ...). The vector isn't free and can be used again.|
|Vect(T)|Vect\_add|vect: Vect(T), T: type, element: T|add element in vector and realloc if vector size is equal to vector capacity (doubling its capacity). return the new vector (usefull after a realloc)|
|e: T|Vect\_pop|vect: Vect(T)|return the last element in the vector and reducing its size|
|size\_t|Vect\_length|vect: Vect(T)|return the length of the vector|

