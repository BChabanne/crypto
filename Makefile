default: run


build: 
	g++ -flto -Wodr -Wall -Werror -Wredundant-decls -Wcast-align -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Wextra -Winvalid-pch -Wformat=2 -Wmissing-format-attribute -Wformat-nonliteral -std=c++14 -o bin main.cpp test.cpp salsa20.cpp

run: build
	./bin
