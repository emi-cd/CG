#include <stdlib.h>
#include <iostream>
#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"

#include "warp.hpp"

namespace Labyrinth {
	int Node[7][5] = {
		{-1, 0,  1,  2, -1},
		{-1, 1,  3,  4, -1},
		{-1, 2,  0,  5,  6},
		{-1, 3, -1, -1, -1},
		{-1, 4,  3,  6, -1},
		{-1, 0,  2,  3, -1},
		{-1, 1,  0,  3, -1},
	};
	int node = 0;

	void set_from(int index, int from) {
		Node[index][0] = from-1;
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
	// 次のシーンへ飛ぶ条件
	switch(Scene) {
		case 0:
			if (ViewPointX < -60) { next(1); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 1:
			if (190 < ViewPointZ) { next(1); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 2:
			if (ViewPointX < -60) { next(1); }
			else if (190 < ViewPointZ) { next(2); }
			else if (60 < ViewPointX) { next(3); }
			break;
		case 3:
			break;
		case 4:
			if (190 < ViewPointZ) { next(1); }
			else if (-60 < ViewPointX) { next(2); }
			break;

	}
	if(ViewPointZ < 0) {
		Labyrinth::get_from();
		make_init();
	}

	std::cout << "Scene:" << Scene << std::endl;
}

// ゴールできるかどうか
bool can_goal(void) {
	int sum = 0;
	for(int i = 0; i < 5; i++)
		sum += mp[i];
	if(sum == 5)
		return true;
	return false;

}

// 次のシーンを設定する
void next(int n){
	int next = Labyrinth::get_node(n+1);
	if(next != -1){
		Scene = next;
		make_init();
	}
	if (can_goal()){
		Scene = 5;
	}

	// Teapot.
	size = std::rand() % 3 + 6;		// Teapot のサイズ
	tea_index = std::rand() % 20;
}

// 視点などの初期化
void make_init() {
	ViewPointX = 0.0;
	ViewPointZ = 0.0;
	SideX = 0.0;
	SideZ = 200.0;
	direction = FRONT;
	rot_y = 0;
}