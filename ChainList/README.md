# DOCUMENTATION

## SYNOPSIS

`#include <chain_list.h>`

content : a complete implementation of chained lists with generals types

call `man chain_list` for informations about availables functions

## DESCRIPTION

### Structs

- ChainListElement
- ChainListData
- ChainList

### Functions

|function|description|args|return|
|--------|-----------|----|------|
|**new\_chain\_list**|create a ChainList struct|sizeof(ElementType)|pointer on ChainList\(ChainList\*\)|
|**chain\_list\_add**|add an element at the and of the list|ChainList\*, \(void\*\) element you want to insert|void|
|**chain\_list\_pop**|remove the last element of the list|ChainList\*|\(void\*\) element removed from the list, NULL if list is empty|
|**chain\_list\_get\_index**|get element at index i|ChainList\*, \(int\) index of element \(start from the end if i\<0\)|\(void\*\) element found, NULL if index out of range|
|**chain\_list\_increment**|set list\-\>current\_pt to list\-\>current\_pt\-\>next|ChainList\*|\(void\*\) element pointed by current\_pt, NULL if end of list|
|**chain\_list\_decrement**|set list\-\>current\_pt to list\-\>current\_pt\-\>previus|ChainList\*|\(void\*\) element pointed by current\_pt, NULL if start of list|
|**chain\_list\_get\_start**|set list\-\>current\_pt to list\-\>data\-\>start|ChainList\*|\(void\*\) return first element, NULL if list is empty|
|**chain\_list\_get\_end**|set list\-\>current\_pt to list\-\>data\-\>end|ChainList\*|\(void\*\) return last element, NULL if list is empty|
|**free\_chain\_list**|free all element in the list, the data struct and the list struct|ChainList\*, (char) 1 if you want to free element inside ChainListElement struct else 0|void|
|**chain\_list\_insert**|add an element at index i|ChainList\*, \(void\*\) element to insert, \(int\) index \(can be negatif if you want to start from the end\) : if index out of range, insert element at begining or at the end|void|
|**chain\_list\_remove**|remove element at index i|ChainList\*, \(int\) index \(can be negatif for the same raison as previus\) : if out of range, remove at end or start \(nothink if empty\)|\(void\*\)return the element removed, NULL if empty|


