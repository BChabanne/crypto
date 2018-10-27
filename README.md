#How code is organised

Functions part of the Salsa20 algorithm are defined in `salsa20.h` and implemented in `salsa.cpp`

`test.h` declare only one function `bool test();`. This function is called from `main`. This function is testing all functions that have been defined in `salsa.h`.

Finaly, some functions for concatenating vectors and for printing vectors and pair are defined in `utility.hpp`.

#How to build and run

By default, you can use `make` to rebuild all the program and launch it.

You can also build it manually :
```
g++ -flto -Wodr -Wall -Werror -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wextra -Winvalid-pch -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -std=c++14 -o bin main.cpp test.cpp salsa20.cpp
```
Once compiled, you can launch the binary : `./bin`

