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

// For Teapot animation... ---------
extern int size;
extern int tea_index;
extern int mp[5];

#endif // _WARP_HPP_