##################### OS data #####################

LIB_PATH= /usr/lib/
INCLUDE_PATH= /usr/include/
MAN3_PATH= /usr/share/man/man3/

####################### All #######################

all: install

obj:
	gcc -fPIC -c linked_list.c

dynamic: obj
	gcc -shared -o liblinked_list.so linked_list.o

static: obj
	ar -rcs liblinked_list.a linked_list.o

install: dynamic
	cp liblinked_list.so $(LIB_PATH)libayaztub_data_structures_linked_list.so
	mkdir -p $(INCLUDE_PATH)ayaztub/data_structures/
	cp linked_list.h $(INCLUDE_PATH)ayaztub/data_structures/
	cp linked_list.t $(MAN3_PATH)ayaztub.data_structures.linked_list.3
	gzip $(MAN3_PATH)ayaztub.data_structures.linked_list.3

test: static
	gcc main.c -L. -llinked_list

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

############### clean & uninstall ##############

clean:
	$(RM) *.o *.out *.a *.so

uninstall:
	$(RM) $(LIB_PATH)libayaztub_data_structures_linked_list
	$(RM) $(INCLUDE_PATH)ayaztub/data_structures/linked_list.h
	$(RM) $(MAN3_PATH)ayaztub.data_structures.linked_list.3.gz


