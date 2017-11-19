#include "iostream"
#include <GLUT/glut.h>
#include "display.hpp"
#include "keybord.hpp"

#include "warp.hpp"

void Warp() {
	switch(Scene) {
		case 0:
			if (ViewPointX < -160) {
				Scene = next(1);
				make_init();
			}
			else if (100 < ViewPointX) {
				Scene = next(2);
				make_init();
			}
			break;
		case 1:
			if (440 < ViewPointY) {
				Scene = next(0);
				make_init();
			}
			else if (100 < ViewPointX) {
				Scene = next(2);
				make_init();
			}
			break;
		case 2:
			if (ViewPointX < -160) {
				Scene = next(0);
				make_init();
			}
			else if(440 < ViewPointY) {
				Scene = next(1);
				make_init();
			}
			else if (100 < ViewPointX) {
				Scene = next(0);
				make_init();
			}
			break;
	}
	std::cout << Scene << std::endl;
}

int next(int n){
	return n;
}

void make_init() {
	ViewPointX = 0.0;
	ViewPointY = 0.0;
	SideX = 0.0;
	SideY = 200.0;
	direction = FRONT;
}