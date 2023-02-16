.TH data_structures 3 "december 10, 2022" "version 1.1" "AyAztuB C library doc : data_structures"

.SH NAME
data_structures \- data structures c library

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

.SH DESCRIPTION
This is a module of futher c libraries.
All of the libraries in it are data struvtures.

.SH CONTENT

.TP
\fBlambda\fR (\fIreturn_type\fR, \fIargs\fR, \fIbody\fR)
utilisation exemples: \fBlambda\fR(\fIint\fR, \fI(\f(BIint\fI e)\fR, \fI{ printf("%d\n", e); return e; }\fR);

.TP
\fBlinked_list\fR
An implementation of linked list (\fBayaztub.data_structures.linked_list\fR(3))

.TP
\fBvect\fR
An implementation of vectors / stacks (\fBayaztub.data_structures.vect\fR(3))

.SH SEE ALSO

\fBayaztub\fR(3), \fBayaztub.data_structures.linked_list\fR(3), \fBayaztub.data_structures.vect\fR(3)

.SH AUTHOR
created by \fBAyAztuB\fR (\fIayaztub@gmail.com\fR) from \fIhttps://github.com/AyAztuB/C_libs\fR



