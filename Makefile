
##################### OS data #####################

LIB_PATH= /usr/lib/
INCLUDE_PATH= /usr/include/
MAN3_PATH= /usr/share/man/man3/

####################### All #######################

all: linked_list_install

################### Linked List ###################

linked_list:
	gcc -c LinkedList/linked_list.c

linked_list_obj:
	gcc -fPIC -c LinkedList/linked_list.c

linked_list_static: linked_list
	ar -rcs liblinked_list.a linked_list.o

linked_list_dynamic: linked_list_obj
	gcc -shared -o liblinked_list.so linked_list.o

linked_list_install: linked_list_dynamic
	cp liblinked_list.so $(LIB_PATH)
	cp LinkedList/linked_list.h $(INCLUDE_PATH)
	cp LinkedList/linked_list.t $(MAN3_PATH)linked_list.3
	gzip $(MAN3_PATH)linked_list.3

##################### clean #####################

clean:
	$(RM) *.o

clean_all:
	$(RM) *.o *.a *.so

################### uninstall ###################

uninstall: uninstall_linked_list

uninstall_linked_list:
	$(RM) $(LIB_PATH)liblinked_list.so $(INCLUDE_PATH)linked_list.h $(MAN3_PATH)linked_list.3.gz

