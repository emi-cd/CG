#ifndef   _KEYBORD_HPP_
#define   _KEYBORD_HPP_

void Keyboard(unsigned char key, int x, int y);
void SpecialKeyBord(int key, int x, int y);

void go_left();
void go_right();
void go_back();
void go_front();

bool can_go();

extern double ViewPointX;
extern double ViewPointY; 
extern double ViewPointZ;
extern double SideX;
extern double SideY;

enum Dir {LEFT, FRONT, RIGHT, BACK};
extern Dir direction;

#endif // _KEYBORD_HPP_