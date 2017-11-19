#include <iostream>
#include <GLUT/glut.h>
#include "warp.hpp"

#include "keybord.hpp"


//----------------------------------------------------
// キーボード入力時に呼び出される関数
//----------------------------------------------------
void Keyboard(unsigned char key, int x, int y){
	switch ( key ) {
		case 'q':
			exit(0);
			break;
		case 'l':
		case 'L':
			SideX += 10.0;
			break;
  		case 'r':
  		case 'R':
			SideX -= 10.0;
			break;
  		default:
			break;
  	}
}

//----------------------------------------------------
// 特殊文字入力時に呼び出される関数
//----------------------------------------------------
void SpecialKeyBord(int key, int x, int y){
	switch (direction) {
		case FRONT:
			switch(key) {
				case GLUT_KEY_LEFT:
					go_left();
					break;
				case GLUT_KEY_RIGHT:
					go_right();
					break;
				case GLUT_KEY_UP:
					ViewPointY += 10.0;
					if(can_go())
						SideY = ViewPointY + 200.0;
					else
						ViewPointY -= 10.0;
					break;
				case GLUT_KEY_DOWN:
					go_back();
					break;
				default:
					break;
			}
			break;
		case LEFT:
			switch(key) {
				case GLUT_KEY_LEFT:
					go_back();
					break;
				case GLUT_KEY_RIGHT:
					go_front();
					break;
				case GLUT_KEY_UP:
					ViewPointX -= 10.0;
					if(can_go())
						SideX = ViewPointX - 200.0;
					else 
						ViewPointX += 10.0;
					break;
				case GLUT_KEY_DOWN:
					go_right();
					break;
				default:
					break;
			}
			break;
		case BACK:
			switch(key) {
				case GLUT_KEY_LEFT:
					go_right();
					break;
				case GLUT_KEY_RIGHT:
					go_left();
					break;
				case GLUT_KEY_UP:
					ViewPointY -= 10.0;
					if(can_go())
						SideY = ViewPointY - 200.0;
					else
						ViewPointY += 10.0;
					break;
				case GLUT_KEY_DOWN:
					go_front();
					break;
				default:
					break;
			}
			break;
		case RIGHT:
			switch(key) {
				case GLUT_KEY_LEFT:
					go_front();
					break;
				case GLUT_KEY_RIGHT:
					go_back();
					break;
				case GLUT_KEY_UP:
					ViewPointX += 10.0;
					if (can_go())
						SideX = ViewPointX + 200.0;
					else
						ViewPointX -= 10.0;
					break;
				case GLUT_KEY_DOWN:
					go_left();
					break;
				default:
					break;
			}
			break;
	}
	Warp();
	std::cout << "direction:" << direction << std::endl;
	std::cout << "Y:" << ViewPointY << ",SideY:" << SideY << std::endl; 
	std::cout << "X:" << ViewPointX << ",SideX:" << SideX << std::endl; 
	std::cout << std::endl;
}

void go_left() {
	SideX = ViewPointX - 200.0;
	SideY = ViewPointY;
	direction = LEFT;
}

void go_right() {
	SideX = ViewPointX + 200.0;
	SideY = ViewPointY;
	direction = RIGHT;
}

void go_back() {
	SideX = ViewPointX;
	SideY = ViewPointY - 200.0;
	direction = BACK;
}

void go_front() {
	SideX = ViewPointX;
	SideY = ViewPointY + 200.0;
	direction = FRONT;
}

bool can_go() {
	switch(Scene) {
		case 0:
			if(ViewPointY < 360 && ViewPointX == 0) 
				return true;
			else if(360 == ViewPointY)
				return true;
			else if(300 < ViewPointY && ViewPointY < 360) {
				ViewPointY = 360;
				SideY = 360;
				return true;
			}
			break;
		case 1:
			if(ViewPointX == 0)
				return true;
			else if(300 < ViewPointY && ViewPointY < 360 && 0 <= ViewPointX) {
				ViewPointY = 360;
				SideY = 360;
				return true;
			}else if(ViewPointY == 360)
				return true;
			break;
		case 2:
			if(ViewPointX == 0)
				return true;
			else if(ViewPointY == 360)
				return true;
			else if(300 < ViewPointY && ViewPointY < 360) {
				ViewPointY = 360;
				SideY = 360;
				return true;
			}
			break;
	}
	return false;
}