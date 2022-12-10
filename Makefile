
##################### OS data #####################

LIB_PATH= /usr/lib/
INCLUDE_PATH= /usr/include/
MAN3_PATH= /usr/share/man/man3/

####################### All #######################

all: all_install

all_obj: data_structures_obj

all_static: all_obj
	ar -rcs libayaztub.a linked_list.o

all_dynamic: all_obj
	gcc -shared -o libayaztub.so linked_list.o

all_install: data_structures_install all_dynamic
	cp libayaztub.so $(LIB_PATH)
	cp ayaztub.h $(INCLUDE_PATH)
	cp ayaztub.t $(MAN3_PATH)ayaztub.3
	gzip $(MAN3_PATH)ayaztub.3

################# Data Structure #################

data_structures_obj: linked_list_obj

data_structures_static: data_structures_obj
	ar -rcs libdata_structures.a linked_list.o

data_structures_dynamic: data_structures_obj
	gcc -shared -o libdata_structures.so linked_list.o

data_structures_install: linked_list_install data_structures_dynamic
	cp libdata_structures.so $(LIB_PATH)libayaztub_data_structures.so
	cp DataStructures/data_structures.h $(INCLUDE_PATH)ayaztub/
	cp DataStructures/data_structures.t $(MAN3_PATH)ayaztub.data_structures.3
	gzip $(MAN3_PATH)ayaztub.data_structures.3

####    Linked list ####

linked_list_obj:
	gcc -fPIC -c DataStructures/LinkedList/linked_list.c

linked_list_static: linked_list_obj
	ar -rcs liblinked_list.a linked_list.o

linked_list_dynamic: linked_list_obj
	gcc -shared -o liblinked_list.so linked_list.o

linked_list_install: linked_list_dynamic
	cp liblinked_list.so $(LIB_PATH)libayaztub_data_structures_linked_list.so
	mkdir -p $(INCLUDE_PATH)ayaztub/data_structures/
	cp DataStructures/LinkedList/linked_list.h $(INCLUDE_PATH)ayaztub/data_structures/
	cp DataStructures/LinkedList/linked_list.t $(MAN3_PATH)ayaztub.data_structures.linked_list.3
	gzip $(MAN3_PATH)ayaztub.data_structures.linked_list.3

##################### clean #####################

clean:
	$(RM) *.o *.a *.so

################### uninstall ###################

uninstall:
	rm -rf $(LIB_PATH)libayaztub* $(INCLUDE_PATH)ayaztub* $(MAN3_PATH)ayaztub*

uninstall_data_structures:
	rm -rf $(LIB_PATH)libayaztub_data_structures* $(INCLUDE_PATH)ayaztub/data_structures* $(MAN3_PATH)ayaztub.data_structures.*

