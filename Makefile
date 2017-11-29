.PHONY: all
all: main

main: main.o display.o scene_one.o scene_two.o scene_three.o keybord.o warp.o
	g++ main.o display.o scene_one.o scene_two.o scene_three.o keybord.o warp.o -framework GLUT -framework OpenGL -mmacosx-version-min=10.8
main.o: main.cpp
	g++ main.cpp -mmacosx-version-min=10.8 -c

display.o : display.cpp
	g++ display.cpp -mmacosx-version-min=10.8 -c 

scene_one.o : scene_one.cpp
	g++ scene_one.cpp -mmacosx-version-min=10.8 -c
	
scene_two.o : scene_two.cpp
	g++ scene_two.cpp -mmacosx-version-min=10.8 -c

scene_three.o : scene_three.cpp
	g++ scene_three.cpp -mmacosx-version-min=10.8 -c

keybord.o : keybord.cpp
	g++ keybord.cpp -mmacosx-version-min=10.8 -c

warp.o : warp.cpp
	g++ warp.cpp -mmacosx-version-min=10.8 -c

.PHONY: clean
clean:
	rm -rf  main.o display.o scene_one.o scene_two.o scene_three.o keybord.o warp.o