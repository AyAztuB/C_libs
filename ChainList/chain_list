.TH chain_list 3 "04 november 2022" "version 1.0" "chain_list lib man page"

.SH NAME
chain_list \- chained list library functions

.SH SYNOPSIS
.B #include <chain_list.h>

.SH DESCRIPTION
The chained list library provides a simple implementation of chained list in C.
The struct and functions are listed below.

.PP
.B List of structs

.RS

.IP ChainList
chained list type. contening a ChainListData and a pointer to a ChainListElement (useful to iter on the list)

.IP ChainListData
data of the chained list (length, sizeof one element, first and last elements)

.IP ChainListElement
stock all datas about the element ((void*) element, pointer to previus and next element)

.RE

.PP
.B List of functions

.RS

.TP
\fBChainList*\fR new_chain_list (\fBsize_t\fR \fItype\fR)
return an empty chained list, argument \fItype\fR is the size of one element (\fBexemple\fR: \fIsizeof(int)\fR)

.TP
\fBvoid\fR chain_list_add (\fBChainList*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR)
create a ChainListElement containing the \fIelement\fR (passed in arguments) and add it at the end of \fIlist\fR

.TP
\fBvoid*\fR chain_list_pop (\fBChainList*\fR \fIlist\fR)
remove the last ChainListElement of the \fIlist\fR and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR chain_list_get_index (\fBChainList*\fR \fIlist\fR, \fBint\fR \fIi\fR)
return content of ChainListElement at index \fIi\fR in \fIlist\fR. Start from the end if \fIi\fR < 0 (\fBexemple\fR: \-1 return last element). return \fBNULL\fR if index out of range. it doesn't modify \f(BIlist\fB\->current_pt\fR

.TP
\fBvoid*\fR chain_list_increment (\fBChainList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->next\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if end of \fIlist\fR)

.TP
\fBvoid*\fR chain_list_decrement (\fBChainList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to \f(BIlist\fB->current_pt\->previus\fR and return the element pointed by \f(BIlist\fB\->current_pt\fR (\fBNULL\fR if start of \fIlist\fR)

.TP
\fBvoid*\fR chain_list_get_start (\fBChainList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the first ChainListElement and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid*\fR chain_list_get_end (\fBChainList*\fR \fIlist\fR)
set \f(BIlist\fB\->current_pt\fR to the last ChainListElement and return its content (\fBNULL\fR if \fIlist\fR is empty)

.TP
\fBvoid\fR free_chain_list (\fBChainList*\fR \fIlist\fR, \fBchar\fR \fIFreeValues\fR)
free all ChainListElement from \fIlist\fR, the ChainListData and the ChainList. if \fIFreeValues\fR is different to 0, also free content of each ChainListElement in the \fIlist\fR

.TP
\fBvoid\fR chain_list_insert (\fBChainList*\fR \fIlist\fR, \fBvoid*\fR \fIelement\fR, \fBint\fR \fIindex\fR)
create a ChainListElement containing the \fIelement\fR and add it in the \fIlist\fR at index \fIindex\fR. start from the end if \fIindex\fR < 0. insert at end or begin if index out of range

.TP
\fBvoid*\fR chain_list_remove (\fBChainList*\fR \fIlist\fR, \fBint\fR \fIindex\fR)
remove ChainListElement at index \fIindex\fR in \fIlist\fR and return its content. start from the end if \fIindex\fR < 0. return \fBNULL\fR if \fIlist\fR is empty. remove first or last element if index out of range

.RE

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/C_libs/tree/main/ChainList\fR


