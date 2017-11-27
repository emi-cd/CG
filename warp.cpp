#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"

#include "warp.hpp"

namespace Labyrinth {
	int Node[7][5] = {
		{-1, 0, 1, 5, -1},
		{-1, 2, 2, 3, 5},
		{-1, 1, 1, 3, -1},
		{-1, 0, 2, 4, -1},
		{-1, 1, 3, 6, -1},
		{-1, 2, 2, 3, 4},
		{-1, 3, -1, -1, -1},
	};
	int node = 0;

	void set_from(int index, int from) {
		Node[index][0] = from;
	} 

	void get_from() {
		if(Node[node][0] != -1)
			Scene = Node[node][0];
	}

	int get_scene() {
		return Node[node][1];
	}

	int get_node(int index) {
		int ret = Node[node][index];
		set_from(ret, node);
		node = ret;

		std::cout << "node:" << node << std::endl;
		return Node[ret][1];
	}
}

void Warp() {
	switch(Scene) {
		case 0:
			if (ViewPointX < -120) { next(1); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 1:
			if (250 < ViewPointY) { next(1); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 2:
			if (ViewPointX < -120) { next(1); }
			else if (250 < ViewPointY) { next(2); }
			else if (60 < ViewPointX) { next(3); }
			break;
	}
	if(ViewPointY < 0) {
		Labyrinth::get_from();
		make_init();
	}

	std::cout << Scene << std::endl;
}

bool can_goal(void) {
	int sum = 0;
	for(int i = 0; i < 5; i++)
		sum += mp[i];
	if(sum == 5)
		return true;
	return false;

}

void next(int n){
	int next = Labyrinth::get_node(n+1);
	if (!can_goal() && next == 3)
		next = 1;
	Scene = next;
	make_init();

	// Teapot.
	size = std::rand() % 3 + 6;		// Teapot のサイズ
	tea_index = std::rand() % 20;
}

void make_init() {
	ViewPointX = 0.0;
	ViewPointY = 0.0;
	SideX = 0.0;
	SideY = 200.0;
	direction = FRONT;
}