default: run


build: 
	g++ -o bin main.cpp test.cpp salsa20.cpp

run: build
	./bin
