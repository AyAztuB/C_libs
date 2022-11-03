# C_libs
my libraries for c

## Install
On windows, just became better 🤣 ...

### Dynamic library

On linux just do `sudo make install` in `C_libs/ChainList` directory

### Static library

You can also obtain a static library using `make static`

If you want, you also can add the `libchain_list.a` in `/usr/lib/`
and the `chain_list.h` in `/usr/include/` but i personally prefer
the synamic one.

## Use

the 2 next section explain how to include the library if you use the makefile

### Dynamic library

If you have put the library in `/usr/lib/` you will be abble to include it
using `#inclide <chain_list.h>` and to compile it using
`gcc main.c -lchain_list -o main`

### Static library

if you haven't put the library in the `/usr/lib/` path, you will need to move
the library and the header file in your code source directory
you will include it with `#include "chain_list.h"` and compile it with
`gcc main.c -L. -lchain_list -o main`

### More generally

You can include it with `<>` instead of `""` if the library and the header are
in `/usr/lib/` and `/usr/include/`.

when you compile it, you will need to use `-lchain_list` to precise you are
using the `libchain_list`. If you include it with `""`, you also will need to
precise the library path using `-L<PATH_TO_LIBRARY>`


## Contact me

If you have a trouble (after research obviously) or for anything else about this project, you can contact me at ayaztub@gmail.com or on discord via private message at `AyAztuB#2419`. When you contact me, please use a specific subject (like _C libs_ or _chain list_) and precisely explain what your problem with.
