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

install_debug:
	$(CC) -DSB3_CRASH_WHEN_ERROR $(CFLAGS) -c -o sb3.o sb3.c
	$(CC) -shared -o $(DYNAMIC) sb3.o
	cp $(DYNAMIC) /usr/lib/
	cp $(HDR) /usr/include/

test_debug:
	$(CC) -DSB3_CRASH_WHEN_ERROR $(CFLAGS) -c -o sb3.o sb3.c
	ar -rcs $(STATIC) sb3.o
	gcc main.c -L. -lsb3

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJ) $(DYNAMIC) $(STATIC) a.out copy.bmp



