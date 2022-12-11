.TH linked_list 3 "december 10, 2022" "version 1.1" "AyAztuB C library doc : linked_list"

.SH NAME
linked_list \- linked list c library

.SH SYNOPSIS

.B #include <ayaztub.h>
.RS
gcc my_program.c \fI\-layaztub\fR
.RE
.PP
.B #include <ayaztub/data_structures.h>
.RS
gcc my_program.c \fI\-layaztub_data_structures\fR
.RE
.PP
.B #include <ayaztub/data_structures/linked_list.h>
.RS
gcc my_program.c \fI\-layaztub_data_structures_linked_list\fR
.RE

.SH DESCRIPTION
The linked list library provides a simple implementation of linked list in C.
The struct and functions are listed below.

.PP
.B List of structs

.RS

.IP linked_list_t
linked list type. contening the length, the sizeof one element, a pointer to the first and to the last element and a pointer to the current element (useful to iter on the list)

.IP linked_list_element_t
stock all datas about the element ((void*) element, pointer to previus and next element)

.RE

.PP
.B List of functions

.RS

.TP
\fBlinked_list_t*\fR new_linked_list (\fBsize_t\fR \fItype\fR)
return an empty linked list, argument \fItype\fR is the size of one element (\fBexemple\fR: \fIsizeof(int)\fR)

.TP
\fBvoid\fR linked_list_add (\fBlinked_list_t*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR)
create a linked_list_element_t containing the \fIelement\fR (passed in arguments) and add it at the end of \fIlist\fR

.TP
\fBvoid*\fR linked_list_pop (\fBlinked_list_t*\fR \fIlist\fR)
remove the last linked_list_element_t of the \fIlist\fR and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR linked_list_get_index (\fBlinked_list_t*\fR \fIlist\fR, \fBint\fR \fIi\fR)
return content of linked_list_element_t at index \fIi\fR in \fIlist\fR. Start from the end if \fIi\fR < 0 (\fBexemple\fR: \-1 return last element). return \fBNULL\fR if index out of range. it doesn't modify \f(BIlist\fB\->current_pt\fR

.TP
\fBvoid*\fR linked_list_increment (\fBlinked_list_t*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->next\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if end of \fIlist\fR)

.TP
\fBvoid*\fR linked_list_decrement (\fBlinked_list_t*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->previus\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if start of \fIlist\fR)

.TP
\fBvoid*\fR linked_list_get_start (\fBlinked_list_t*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the first linked_list_element_t and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR linked_list_get_end (\fBlinked_list_t*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the last linked_list_element_t and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid\fR free_linked_list (\fBlinked_list_t*\fR \fIlist\fR, \fBchar\fR \fIFreeValues\fR)
free all linked_list_element_t from \fIlist\fR, and the linked_list_t. if \fIFreeValues\fR is different to 0, also free content of each linked_list_element_t in the \fIlist\fR

.TP
\fBvoid\fR linked_list_insert (\fBlinked_list_t*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR, \fBint\fR \fIindex\fR)
create a linked_list_element_t containing the \fIelement\fR and add it in the \fIlist\fR at index \fIindex\fR. start from the end if \fIindex\fR < 0. insert at end or begin if index out of range

.TP
\fBvoid*\fR linked_list_remove (\fBlinked_list_t*\fR \fIlist\fR, \fBint\fR \fIindex\fR)
remove linked_list_element_t at index \fIindex\fR in \fIlist\fR and return its content. start from the end if \fIindex\fR < 0. return \fBNULL\fR if \fIlist\fR is empty. remove first or last element if index out of range

.RE

.SH SEE ALSO

\fBayaztub\fR(3), \fBayaztub.data_structures\fR(3)

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/C_libs\fR


