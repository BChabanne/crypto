default: run


build: 
	g++ -Werror -std=c++14 -o bin main.cpp test.cpp salsa20.cpp

run: build
	./bin
