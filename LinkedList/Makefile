DYNAMIC = liblinked_list.so
STATIC = liblinked_list.a
HDR = linked_list.h
SRC = linked_list.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: install


dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static: $(OBJ)
	ar -rcs $(STATIC) $(OBJ)

install: dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/
	cp linked_list.t /usr/share/man/man3/linked_list.3
	gzip /usr/share/man/man3/linked_list.3

test: static
	gcc main.c -L. -llinked_list

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC) a.out

uninstall:
	$(RM) /usr/lib/$(DYNAMIC) /usr/include/$(HDR) /usr/share/man/man3/linked_list.3.gz


