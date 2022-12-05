.TH linked_list 3 "december 05, 2022" "version 1.1" "linked_list lib man page"

.SH NAME
linked_list \- linked list library functions

.SH SYNOPSIS
.B #include <linked_list.h>

.SH DESCRIPTION
The linked list library provides a simple implementation of linked list in C.
The struct and functions are listed below.

.PP
.B List of structs

.RS

.IP LinkedList
linked list type. contening a LinkedListData and a pointer to a LinkedListElement (useful to iter on the list)

.IP LinkedListData
data of the linked list (length, sizeof one element, first and last elements)

.IP LinkedListElement
stock all datas about the element ((void*) element, pointer to previus and next element)

.RE

.PP
.B List of functions

.RS

.TP
\fBLinkedList*\fR new_linked_list (\fBsize_t\fR \fItype\fR)
return an empty linked list, argument \fItype\fR is the size of one element (\fBexemple\fR: \fIsizeof(int)\fR)

.TP
\fBvoid\fR linked_list_add (\fBLinkedList*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR)
create a LinkedListElement containing the \fIelement\fR (passed in arguments) and add it at the end of \fIlist\fR

.TP
\fBvoid*\fR linked_list_pop (\fBLinkedList*\fR \fIlist\fR)
remove the last LinkedListElement of the \fIlist\fR and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR linked_list_get_index (\fBLinkedList*\fR \fIlist\fR, \fBint\fR \fIi\fR)
return content of LinkedListElement at index \fIi\fR in \fIlist\fR. Start from the end if \fIi\fR < 0 (\fBexemple\fR: \-1 return last element). return \fBNULL\fR if index out of range. it doesn't modify \f(BIlist\fB\->current_pt\fR

.TP
\fBvoid*\fR linked_list_increment (\fBLinkedList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->next\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if end of \fIlist\fR)

.TP
\fBvoid*\fR linked_list_decrement (\fBLinkedList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->previus\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if start of \fIlist\fR)

.TP
\fBvoid*\fR linked_list_get_start (\fBLinkedList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the first LinkedListElement and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR linked_list_get_end (\fBLinkedList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the last LinkedListElement and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid\fR free_linked_list (\fBLinkedList*\fR \fIlist\fR, \fBchar\fR \fIFreeValues\fR)
free all LinkedListElement from \fIlist\fR, the LinkedListData and the LinkedList. if \fIFreeValues\fR is different to 0, also free content of each LinkedListElement in the \fIlist\fR

.TP
\fBvoid\fR linked_list_insert (\fBLinkedList*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR, \fBint\fR \fIindex\fR)
create a LinkedListElement containing the \fIelement\fR and add it in the \fIlist\fR at index \fIindex\fR. start from the end if \fIindex\fR < 0. insert at end or begin if index out of range

.TP
\fBvoid*\fR linked_list_remove (\fBLinkedList*\fR \fIlist\fR, \fBint\fR \fIindex\fR)
remove LinkedListElement at index \fIindex\fR in \fIlist\fR and return its content. start from the end if \fIindex\fR < 0. return \fBNULL\fR if \fIlist\fR is empty. remove first or last element if index out of range

.RE

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/C_libs/tree/main/LinkedList\fR


