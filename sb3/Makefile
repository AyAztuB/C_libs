DYNAMIC = libsb3.so
STATIC = libsb3.a
HDR = sb3.h
SRC = sb3.c
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: install

dynamic: $(OBJ)
	$(CC) -shared -o $(DYNAMIC) $(OBJ)

static: $(OBJ)
	ar -rcs $(STATIC) $(OBJ)

test: static
	gcc main.c -L. -lsb3

install: dynamic
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC) a.out *.bmp



