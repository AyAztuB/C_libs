# DOCUMENTATION

## SYNOPSIS

`#include <ayaztub/data_structures/linked_list.h>`

content : a complete implementation of linked lists with generals types

call `man ayaztub.data_structures.linked_list` for informations about availables functions

## DESCRIPTION

### Structs

- LinkedListElement
- LinkedListData
- LinkedList

### Functions

|function|description|args|return|
|--------|-----------|----|------|
|**new\_linked\_list**|create a LinkedList struct|sizeof(ElementType)|pointer on LinkedList\(LinkedList\*\)|
|**linked\_list\_add**|add an element at the and of the list|LinkedList\*, \(void\*\) element you want to insert|void|
|**linked\_list\_pop**|remove the last element of the list|LinkedList\*|\(void\*\) element removed from the list, NULL if list is empty|
|**linked\_list\_get\_index**|get element at index i|LinkedList\*, \(int\) index of element \(start from the end if i\<0\)|\(void\*\) element found, NULL if index out of range|
|**linked\_list\_increment**|set list\-\>current\_pt to list\-\>current\_pt\-\>next|LinkedList\*|\(void\*\) element pointed by current\_pt, NULL if end of list|
|**linked\_list\_decrement**|set list\-\>current\_pt to list\-\>current\_pt\-\>previus|LinkedList\*|\(void\*\) element pointed by current\_pt, NULL if start of list|
|**linked\_list\_get\_start**|set list\-\>current\_pt to list\-\>data\-\>start|LinkedList\*|\(void\*\) return first element, NULL if list is empty|
|**linked\_list\_get\_end**|set list\-\>current\_pt to list\-\>data\-\>end|LinkedList\*|\(void\*\) return last element, NULL if list is empty|
|**free\_linked\_list**|free all element in the list, the data struct and the list struct|LinkedList\*, (char) 1 if you want to free element inside LinkedListElement struct else 0|void|
|**linked\_list\_insert**|add an element at index i|LinkedList\*, \(void\*\) element to insert, \(int\) index \(can be negatif if you want to start from the end\) : if index out of range, insert element at begining or at the end|void|
|**linked\_list\_remove**|remove element at index i|LinkedList\*, \(int\) index \(can be negatif for the same raison as previus\) : if out of range, remove at end or start \(nothink if empty\)|\(void\*\)return the element removed, NULL if empty|


