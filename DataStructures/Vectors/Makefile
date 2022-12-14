##################### OS data #####################

LIB_PATH= /usr/lib/
INCLUDE_PATH= /usr/include/
MAN3_PATH= /usr/share/man/man3/

####################### All #######################

all: install

install:
	mkdir -p $(INCLUDE_PATH)ayaztub/data_structures/
	cp vect.h $(INCLUDE_PATH)ayaztub/data_structures/
	cp vect.t $(MAN3_PATH)ayaztub.data_structures.vect.3
	gzip $(MAN3_PATH)ayaztub.data_structures.vect.3

test: static
	gcc main.c

############### clean & uninstall ##############

clean:
	$(RM) *.o *.out *.a *.so

uninstall:
	$(RM) $(INCLUDE_PATH)ayaztub/data_structures/vect.h
	$(RM) $(MAN3_PATH)ayaztub.data_structures.vect.3.gz


