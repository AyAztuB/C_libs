# Data structures

## Synopsis

```
#include <ayaztub/data_structures.h>
```
```
gcc main.c -layaztub_data_structures
```
```
man ayaztub.data_structures
```

## Content

### Lambda function

The header file also contains a macro to define lambda function:
`lambda(return_type, args, body)`
It can be used like in the following exemple:
```
int (*lambda_fct) (int) = lambda(int, (int e), { printf("%d\n", e); return e; });
```

### Linked List

**Include**
```
#include <ayaztub/data_structures/linked_list.h>
```
**Library name**
```
libayaztub_data_structures_linked_list
```
**Compilation**
```
gcc main.c -layaztub_data_structures_linked_list
```
**MAN page**
```
man ayaztub.data_structures.linked_list
man ./LinkedList/linked_list.t
```

### Vectors

**Include**
```
#include <ayaztub/data_structures/vect.h>
```
**MAN page**
```
man ayaztub.data_structures.vect
man ./Vectors/vect.t
```

