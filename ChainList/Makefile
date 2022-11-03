DYNAMIC = libchain_list.so
STATIC = libchain_list.a
HDR = chain_list.h
SRC = chain_list.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror

dynamic:
	$(CC) $(CFLAGS) -fPIC -c -o $(OBJ) $(SRC)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static:
	$(CC) $(CFLAGS) -c -o $(OBJ) $(SRC)
	ar -rcs $(STATIC) $(OBJ)

install:
	make dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC)

