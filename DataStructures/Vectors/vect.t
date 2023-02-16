.TH vect 3 "december 16, 2022" "version 1.1" "AyAztuB C library doc: vect"

.SH NAME
vect \- vector c library

.SH SYNOPSIS

.B #include <ayaztub.h>
.PP
.B #include <ayaztub/data_structures.h>
.PP
.B #include <ayaztub/data_structures/vect.h>

.SH CONTAINS
The header file also contain a macro to define a lambda function (usefull for
the \fBVect_print\fR function):
.PP
.RS
.TP
\fBlambda\fR (\fIreturn_type\fR, \fIargs\fR, \fIbody\fR)
utilisation exemples: \fBlambda\fR(\fIint\fR, \fI(\f(BIint\fI e)\fR, \fI{ printf("%d\n", e); return e; }\fR);
.RE

.SH DESCRIPTION
This library provides a simple implementation of vectors in C.
It can be used with any types and it's used lake a stack.
The struct, defines, ... are listed below.

.PP
.B Define
.RS
.IP Vect(T)
equal to T* with T a type, its usefull to separate pointer returned as vect from your own.
.RE

.PP
.B Defines as functions
.RS

.TP
\fBVect(T)\fR Vect_init (\fBTYPE\fR \fIT\fR, \fBsize_t\fR \fIcapacity\fR)
create and return a vector of type \fIT\fR with \fIcapacity\fR as its initial capacity.

.TP
\fBVect(T)\fR Vect_new (\fBTYPE\fR \fIT\fR)
create and return a vector of type \fIT\fR with a default capacity of 4.

.TP
\fBvoid\fR Vect_free (\fBVect(T)\fR \fIvect\fR)
free the \fIvect\fR

.TP
\fBvoid\fR Vect_free_content (\fBVect(T)\fR \fIvect\fR)
free all elements in the \fIvect\fR (these elements must have been allocated). The \fIvect\fR is still usefull.

.TP
\fBVect(T)\fR Vect_push (\fBVect(T)\fR \fIvect\fR, \fBTYPE\fR \fIT\fR, \fBT\fR \fIelement\fR)
add the \fIelement\fR add the end of the \fIvect\fR. If the length of the \fIvect\fR is equal to it's capacity, it will be reallocated with the double of its capacity

.TP
\fBT\fR Vect_pop (\fBVect(T)\fR \fIvect\fR)
reduce the length of the \fIvect\fR by one and return its last element

.TP
\fBsize_t\fR Vect_length (\fBVect(T)\fR \fIvect\fR)
return the length of the \fIvect\fR

.TP
\fBvoid\fR Vect_print (\fBVect(T)\fR \fIvect\fR, \fBvoid\fR \fI(*print_fct)(\fBT\fI)\fR)
print the vector as follow: { print_fct(e1) print_fct(e2) ... }\\n with \fIprint_fct\fR a fonction to print one element of the vector \fIvect\fR.

.SH SEE ALSO

\fBayaztub\fR(3), \fBayaztub.data_structures\fR(3)

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/C_libs\fR


