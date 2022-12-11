# DOCUMENTATION

## SYNOPSIS

`#include <ayaztub/data_structures/linked_list.h>`

content : a complete implementation of linked lists with generals types

call `man ayaztub.data_structures.linked_list` for informations about availables functions

## DESCRIPTION

### Structs

- linked\_list\_element\_t
- linked\_list\_t

### Functions

|function|description|args|return|
|--------|-----------|----|------|
|**new\_linked\_list**|create a linked\_list\_t struct|sizeof(ElementType)|pointer on linked\_list\_t\(linked\_list\_t\*\)|
|**linked\_list\_add**|add an element at the and of the list|linked\_list\_t\*, \(void\*\) element you want to insert|void|
|**linked\_list\_pop**|remove the last element of the list|linked\_list\_t\*|\(void\*\) element removed from the list, NULL if list is empty|
|**linked\_list\_get\_index**|get element at index i|linked\_list\_t\*, \(int\) index of element \(start from the end if i\<0\)|\(void\*\) element found, NULL if index out of range|
|**linked\_list\_increment**|set list\-\>current\_pt to list\-\>current\_pt\-\>next|linked\_list\_t\*|\(void\*\) element pointed by current\_pt, NULL if end of list|
|**linked\_list\_decrement**|set list\-\>current\_pt to list\-\>current\_pt\-\>previus|linked\_list\_t\*|\(void\*\) element pointed by current\_pt, NULL if start of list|
|**linked\_list\_get\_start**|set list\-\>current\_pt to list\-\>data\-\>start|linked\_list\_t\*|\(void\*\) return first element, NULL if list is empty|
|**linked\_list\_get\_end**|set list\-\>current\_pt to list\-\>data\-\>end|linked\_list\_t\*|\(void\*\) return last element, NULL if list is empty|
|**free\_linked\_list**|free all element in the list, the data struct and the list struct|linked\_list\_t\*, (char) 1 if you want to free element inside linked\_list\_element\_t struct else 0|void|
|**linked\_list\_insert**|add an element at index i|linked\_list\_t\*, \(void\*\) element to insert, \(int\) index \(can be negatif if you want to start from the end\) : if index out of range, insert element at begining or at the end|void|
|**linked\_list\_remove**|remove element at index i|linked\_list\_t\*, \(int\) index \(can be negatif for the same raison as previus\) : if out of range, remove at end or start \(nothink if empty\)|\(void\*\)return the element removed, NULL if empty|


