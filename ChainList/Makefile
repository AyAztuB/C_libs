DYNAMIC = libchain_list.so
STATIC = libchain_list.a
HDR = chain_list.h
SRC = chain_list.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: install


dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static: $(OBJ)
	ar -rcs $(STATIC) $(OBJ)

install:
	make dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC)


