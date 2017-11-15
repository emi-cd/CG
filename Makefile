.PHONY: all
all: main

main: main.o display.o
	g++ main.o display.o -framework GLUT -framework OpenGL -mmacosx-version-min=10.8

main.o: main.cpp
	g++ main.cpp -mmacosx-version-min=10.8 -c

display.o : display.cpp
	g++ display.cpp -mmacosx-version-min=10.8 -c

	
.PHONY: clean
clean:
	rm -rf  main.o display.o