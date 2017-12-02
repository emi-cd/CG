#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <list>
#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"

#include "warp.hpp"

// シーンの数　+ 1
const int SCENE = 4;

// シーン事の行く先の数
int scene_mp[SCENE] = {2, 2, 3, 2};
std::list<int> where_from;

 Node *make_node(const int scene, Node* parent){
  Node *node = (Node*)malloc(sizeof(Node));
  if (node != NULL) {
    node->scene = scene;
    node->num = scene_mp[scene];
    node->parent = parent;
    node->child_one = NULL;
	node->child_two = NULL;
	node->child_three = NULL;
  }
  return node;
}

Node *insert_node(Node *parent) {
	Node *node = make_node(rand()%SCENE, parent);
	node->child_one = make_node(rand()%SCENE, node);
	node->child_two = make_node(rand()%SCENE, node);
	node->child_three = make_node(rand()%SCENE, node);
	
	return node;
}

Node *make_Labyrinth(){
	srand((unsigned)time(NULL));
	Node* n = make_node(Scene, NULL);
	n->child_one = insert_node(n);
	n->child_two = insert_node(n);
	n->child_three = insert_node(n);
	return n;
}

void Warp() {
	// 次のシーンへ飛ぶ条件
	switch(Scene) {
		case 0:
			if (ViewPointX < -60) { next(1); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 1:
			if (190 < ViewPointZ) { next(3); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 2:
			if (ViewPointX < -60) { next(1); }
			else if (190 < ViewPointZ) { next(3); }
			else if (60 < ViewPointX) { next(2); }
			break;
		case 3:
			if (190 < ViewPointZ) { next(3); }
			else if (ViewPointX < -60) { next(1); }
			break;
	}
	if(ViewPointZ < 0) {
		if(node->parent){
			old_scene = Scene;
			node = node->parent;
			Scene = node->scene;

			// とりあえずパッチ--------
			int index = where_from.back();
			where_from.pop_back();
			if(Scene == 0 && index == 3)
				index = 1;
			else if(Scene == 1 && index == 1)
				index = 2;
			else if(Scene == 3 && index == 2)
				index = 1;
			// ---------------------

			switch(index){
				case 1:
					ViewPointX = -60.0;
					ViewPointZ = 130.0;
					SideX = -60.0;
					SideZ = 330.0;
					direction = LEFT;
					rot_y = 270.0;
					break;
				case 2:
					ViewPointX = 60.0;
					ViewPointZ = 130.0;
					SideX = 60.0;
					SideZ = 330.0;
					direction = RIGHT;
					rot_y = 90.0;
					break;
				case 3:
					ViewPointX = 0.0;
					ViewPointZ = 200.0;
					SideX = 0.0;
					SideZ = 400.0;
					direction = BACK;
					rot_y = 180.0;
					break;
			}
		}
	}

	std::cout << "Scene:" << Scene << std::endl;
}

// 次のシーンを設定する
void next(int n){
	where_from.push_back(n); 
	switch(n){
		case 1:
			if(node->child_one){
				node = node->child_one;
			}else{
				node->child_one = make_node(4, node);
			}
			break;
		case 2:
			if(node->child_two){
				node = node->child_two;
			}else{
				node->child_two = make_node(4, node);
			}
			break;
		case 3:
			if(node->child_three){
				node = node->child_three;
			}else{
				node->child_three = make_node(4, node);
			}
			break;
	}
	old_scene = Scene;
	Scene = node->scene;

	make_init();

	// Teapot.
	size = std::rand() % 3 + 6;		// Teapot のサイズ
	tea_index = std::rand() % 10;
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