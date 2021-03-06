#ifndef   _WARP_HPP_
#define   _WARP_HPP_

void Warp(void);
void next(int n);
void make_init();


extern int Scene;

extern double ViewPointX;
extern double ViewPointY; 
extern double ViewPointZ;
extern double SideX;
extern double SideZ;

extern float rot_y;

extern int old_scene;


// 迷路を作る
typedef struct node{
	int scene;
	int num;
	struct node* parent;
	struct node* child_one;
	struct node* child_two;
	struct node* child_three;
} Node;
extern Node* node;
Node *make_Labyrinth();

// For Teapot animation... ---------
extern int size;
extern int tea_index;
extern int mp[5];

#endif // _WARP_HPP_