# C_libs

AyAztuB's C Library.
In continuous development

## Introduction

This is a collection of tools for the C programming.

## Compile in static or dynamic library

You can use the global Makefile or a subdirectory Makefile
From the global one, just do (with `<LIBRARY>` the library to compile and
`<METHODE>` the static or dynamic methode)
```
make <LIBRARY>_<METHODE>
```
For example, the LinkedList library is compiled as follow:
```
make linked_list_static
make linked_list_dynamic
```
By using the subdirectory Makefile, you just need to precise the methode:
```
make static
make dynamic
```
A main.c program is also provided and you can test the library on it with the
following command.
```
make test
```
If you are in a subdirectory, you can clean all compile files with
```
make clean
```
At the repository root, this command will only remove .o files but compiled
libraries will be still here. If you want to clean all of this, you need to use
```
make clean_all
```

## Install
On windows, just became better 🤣 ...

You can also install the dynamic library in your system.
By default, the library will be installed at `/usr/lib/`, the header at
`/usr/include/` and the man page at `/usr/share/man/man3/`
If your systems path aren't the aboves, you can change it at the begining of the
main Makefile

To install the libraries, just do
```
sudo make <LIBRARY>_install
```
with `<LIBRARY>` the library to install. For exemple, with the LinkedList
library, it's as follow
```
sudo make linked_list_install
```
If you want to install all of the libraries, you can do
```
sudo make
```

To uninstall a specific library, you can do
```
sudo make uninstall_<LIBRARY>
```
You can uninstall all of the libraries with
```
sudo make uninstall
```

## Use

### Installed Library

```
#include <LIBRARY.h>
```
with `LIBRARY` the name of it (for exemple: `#include <linked_list.h>`)
To compile your program with it, don't forgot to link with the library:
```
gcc main.c -lLIBRARY
```
(for exemple `gcc main.c -llinked_list`)

### Static library

If you haven't put the library in the `/usr/lib/` path, you will need to move
the library and the header file in your code source directory
you will include it with `#include "linked_list.h"` and compile it with
`gcc main.c -L. -llinked_list -o main`
You also can compile your program like `gcc main.c libLIBRARY.a` (for exemple:
`gcc main.c liblinked_list.a`). So on, you can include it with `<>` instead of
`""`

## Content

For specific documentation, please refer to the README in the subdirectory or
use the given man page (if not installed: `man ./LinkedList/linked_list.t`)

### Linked List

**Include**
```
#include <linked_list.h>
```
**Library name**
```
liblinked_list
```

## Contact me

If you have a trouble (after research obviously) or for anything else about this project, you can contact me at ayaztub@gmail.com or on discord via private message at `AyAztuB#2419`. When you contact me, please use a specific subject (like _C libs_ or _linked list_) and precisely explain what your problem with.
